#include "testfs.h"
#include "list.h"
#include "super.h"
#include "block.h"
#include "inode.h"

#define MAX_FILE_SIZE 34376597504

/* given logical block number, read the corresponding physical block into block.
 * return physical block number.
 * returns 0 if physical block does not exist.
 * returns negative value on other errors. */
static int
testfs_read_block(struct inode *in, int log_block_nr, char *block)
{
	int phy_block_nr = 0;

	assert(log_block_nr >= 0);
	if (log_block_nr < NR_DIRECT_BLOCKS) {
		phy_block_nr = (int)in->in.i_block_nr[log_block_nr];
	} else {
		log_block_nr -= NR_DIRECT_BLOCKS;

		if (log_block_nr >= NR_INDIRECT_BLOCKS){
			// TBD();
			log_block_nr -= NR_INDIRECT_BLOCKS;
			int level_one_dindir_index = log_block_nr / NR_INDIRECT_BLOCKS;
			int level_two_dindir_index = log_block_nr % NR_INDIRECT_BLOCKS;
			if (level_one_dindir_index >= NR_INDIRECT_BLOCKS) return -EFBIG;
			if (in->in.i_dindirect > 0){
				read_blocks(in->sb, block, in->in.i_dindirect, 1);
				phy_block_nr = ((int *)block)[level_one_dindir_index];
				if (phy_block_nr > 0){
					read_blocks(in->sb, block, phy_block_nr, 1);
					phy_block_nr = ((int *)block)[level_two_dindir_index];
				}
			}
		}
		else if (in->in.i_indirect > 0) {
			read_blocks(in->sb, block, in->in.i_indirect, 1);
			phy_block_nr = ((int *)block)[log_block_nr];
		}
	}
	if (phy_block_nr > 0) {
		read_blocks(in->sb, block, phy_block_nr, 1);
	} else {
		/* we support sparse files by zeroing out a block that is not
		 * allocated on disk. */
		bzero(block, BLOCK_SIZE);
	}
	return phy_block_nr;
}

int
testfs_read_data(struct inode *in, char *buf, off_t start, size_t size)
{
	char block[BLOCK_SIZE];
	long block_nr = start / BLOCK_SIZE; // logical block number in the file
	long block_ix = start % BLOCK_SIZE; //  index or offset in the block
	int ret;
	const size_t ori_size = size;

	assert(buf);
	if (start + (off_t) size > in->in.i_size) {
		size = in->in.i_size - start;
	}
	if (block_ix + size > BLOCK_SIZE) {
		if ((ret = testfs_read_block(in, block_nr, block)) < 0) return ret;
		memcpy(buf, block + block_ix, BLOCK_SIZE - block_ix);
		size -= BLOCK_SIZE - block_ix;
		buf += BLOCK_SIZE - block_ix;
		block_ix = 0;
		++block_nr;
		while (size > BLOCK_SIZE){
			if ((ret = testfs_read_block(in, block_nr, block)) < 0) return ret;
			memcpy(buf,block,BLOCK_SIZE);
			size -= BLOCK_SIZE;
			buf += BLOCK_SIZE;
			++block_nr;
		}
	}
	if ((ret = testfs_read_block(in, block_nr, block)) < 0)
		return ret;
	memcpy(buf, block + block_ix, size);
	/* return the number of bytes read or any error */
	return ori_size;
}

/* given logical block number, allocate a new physical block, if it does not
 * exist already, and return the physical block number that is allocated.
 * returns negative value on error. */
static int
testfs_allocate_block(struct inode *in, int log_block_nr, char *block)
{
	int phy_block_nr;
	char indirect[BLOCK_SIZE];
	char dindirect_one[BLOCK_SIZE];
	char dindirect_two[BLOCK_SIZE];
	int indirect_allocated = 0;
	int dindirect_one_allocated = 0;
	int dindirect_two_allocated = 0;

	assert(log_block_nr >= 0);
	phy_block_nr = testfs_read_block(in, log_block_nr, block);

	/* phy_block_nr > 0: block exists, so we don't need to allocate it, 
	   phy_block_nr < 0: some error */
	if (phy_block_nr != 0)
		return phy_block_nr;

	/* allocate a direct block */
	if (log_block_nr < NR_DIRECT_BLOCKS) {
		assert(in->in.i_block_nr[log_block_nr] == 0);
		phy_block_nr = testfs_alloc_block_for_inode(in);
		if (phy_block_nr >= 0) {
			in->in.i_block_nr[log_block_nr] = phy_block_nr;
		}
		return phy_block_nr;
	}

	log_block_nr -= NR_DIRECT_BLOCKS;
	if (log_block_nr >= NR_INDIRECT_BLOCKS) {
		log_block_nr -= NR_INDIRECT_BLOCKS;
		int level_one_dindir_index = log_block_nr / NR_INDIRECT_BLOCKS;
		int level_two_dindir_index = log_block_nr % NR_INDIRECT_BLOCKS;
		if (level_one_dindir_index >= NR_INDIRECT_BLOCKS) return -EFBIG;
		if (in->in.i_dindirect == 0) {
			bzero(dindirect_one, BLOCK_SIZE);
			phy_block_nr = testfs_alloc_block_for_inode(in);
			if (phy_block_nr < 0) return phy_block_nr;
			dindirect_one_allocated = 1;
			in->in.i_dindirect = phy_block_nr;
		}
		else read_blocks(in->sb, dindirect_one, in->in.i_dindirect, 1);

		if (((int *)dindirect_one)[level_one_dindir_index] == 0){
			bzero(dindirect_two, BLOCK_SIZE);
			phy_block_nr = testfs_alloc_block_for_inode(in);
			if(phy_block_nr >= 0) {
				((int *)dindirect_one)[level_one_dindir_index] = phy_block_nr;
				dindirect_two_allocated = 1;
			}
			else if (dindirect_one_allocated) {
				testfs_free_block_from_inode (in, in->in.i_dindirect);
				in->in.i_dindirect = 0;
				return phy_block_nr;
			}
		}
		else read_blocks(in->sb,dindirect_two,((int *)dindirect_one)[level_one_dindir_index],1);
		assert(((int *)dindirect_two)[level_two_dindir_index] == 0);
		phy_block_nr = testfs_alloc_block_for_inode(in);
		if(phy_block_nr >= 0) {
			((int *)dindirect_two)[level_two_dindir_index] = phy_block_nr;
			write_blocks(in->sb, dindirect_two, ((int *)dindirect_one)[level_one_dindir_index], 1);
			write_blocks(in->sb, dindirect_one, in->in.i_dindirect, 1);
		}
		else if (dindirect_two_allocated){
			testfs_free_block_from_inode(in,((int *)dindirect_one)[level_one_dindir_index]);
			((int *)dindirect_one)[level_one_dindir_index] = 0;
			if (dindirect_one_allocated){
				testfs_free_block_from_inode(in, in->in.i_dindirect);
				in->in.i_dindirect = 0;
			}
		}
		return phy_block_nr;
	}

	else if (in->in.i_indirect == 0) {	/* allocate an indirect block */
		bzero(indirect, BLOCK_SIZE);
		phy_block_nr = testfs_alloc_block_for_inode(in);
		if (phy_block_nr < 0)
			return phy_block_nr;
		indirect_allocated = 1;
		in->in.i_indirect = phy_block_nr;
	} else {	/* read indirect block */
		read_blocks(in->sb, indirect, in->in.i_indirect, 1);
	}
	/* allocate direct block */
	assert(((int *)indirect)[log_block_nr] == 0);	
	phy_block_nr = testfs_alloc_block_for_inode(in);

	if (phy_block_nr >= 0) {
		/* update indirect block */
		((int *)indirect)[log_block_nr] = phy_block_nr;
		write_blocks(in->sb, indirect, in->in.i_indirect, 1);
	} else if (indirect_allocated) {
		/* there was an error while allocating the direct block, 
		 * free the indirect block that was previously allocated */
		testfs_free_block_from_inode(in, in->in.i_indirect);
		in->in.i_indirect = 0;
	}
	return phy_block_nr;
}

int
testfs_write_data(struct inode *in, const char *buf, off_t start, size_t size)
{
	char block[BLOCK_SIZE];
	long block_nr = start / BLOCK_SIZE; // logical block number in the file
	long block_ix = start % BLOCK_SIZE; //  index or offset in the block
	int ret;
	const size_t ori_size = size;

	if (block_ix + size > BLOCK_SIZE) {
		if ((ret = testfs_allocate_block(in, block_nr, block)) < 0)
			return ret;
		memcpy(block + block_ix, buf, BLOCK_SIZE - block_ix);
		write_blocks(in->sb, block, ret, 1);
		size -= BLOCK_SIZE - block_ix;
		buf += BLOCK_SIZE - block_ix;
		start += BLOCK_SIZE - block_ix;
		in->in.i_size = MAX(in->in.i_size, start);
		block_ix = 0;
		++block_nr;
		while (size > BLOCK_SIZE){
			if ((ret = testfs_allocate_block(in, block_nr, block)) < 0) {
				return ret;
			}
			memcpy(block, buf, BLOCK_SIZE);
			write_blocks(in->sb, block, ret, 1);
			size -= BLOCK_SIZE;
			buf += BLOCK_SIZE;
			start += BLOCK_SIZE;
			in->in.i_size = MAX(in->in.i_size, start);
			++block_nr;
		}
	}
	/* ret is the newly allocated physical block number */
	ret = testfs_allocate_block(in, block_nr, block);
	if (ret < 0)
		return ret;
	memcpy(block + block_ix, buf, size);
	write_blocks(in->sb, block, ret, 1);
	/* increment i_size by the number of bytes written. */
	if (size > 0)
		in->in.i_size = MAX(in->in.i_size, start + (off_t) size);
	in->i_flags |= I_FLAGS_DIRTY;
	/* return the number of bytes written or any error */
	return MIN(ori_size,(size_t)MAX_FILE_SIZE - (size_t)start);
}

int
testfs_free_blocks(struct inode *in)
{
	int i;
	int e_block_nr;

	/* last logical block number */
	e_block_nr = DIVROUNDUP(in->in.i_size, BLOCK_SIZE);

	/* remove direct blocks */
	for (i = 0; i < e_block_nr && i < NR_DIRECT_BLOCKS; i++) {
		if (in->in.i_block_nr[i] == 0)
			continue;
		testfs_free_block_from_inode(in, in->in.i_block_nr[i]);
		in->in.i_block_nr[i] = 0;
	}
	e_block_nr -= NR_DIRECT_BLOCKS;

	/* remove indirect blocks */
	if (in->in.i_indirect > 0) {
		char block[BLOCK_SIZE];
		assert(e_block_nr > 0);
		read_blocks(in->sb, block, in->in.i_indirect, 1);
		for (i = 0; i < e_block_nr && i < NR_INDIRECT_BLOCKS; i++) {
			if (((int *)block)[i] == 0)
				continue;
			testfs_free_block_from_inode(in, ((int *)block)[i]);
			((int *)block)[i] = 0;
		}
		testfs_free_block_from_inode(in, in->in.i_indirect);
		in->in.i_indirect = 0;
	}

	e_block_nr -= NR_INDIRECT_BLOCKS;
	/* handle double indirect blocks */
	if (e_block_nr > 0) {
		// TBD();
		char dindirect_one[BLOCK_SIZE];
		char dindirect_two[BLOCK_SIZE];
		read_blocks(in->sb, dindirect_one, in->in.i_dindirect, 1);
		for (i = 0; i < NR_INDIRECT_BLOCKS; ++i){
			if (((int *)dindirect_one)[i] == 0) continue;
			read_blocks(in->sb, dindirect_two, ((int *)dindirect_one)[i], 1);
			for (int j = 0; j < NR_INDIRECT_BLOCKS; ++j){
				if (((int *)dindirect_two)[j] == 0) continue;
				testfs_free_block_from_inode(in, ((int *)dindirect_two)[j]);
				((int *)dindirect_two)[j] = 0;
			}
			testfs_free_block_from_inode(in, ((int *)dindirect_one)[i]);
			((int *)dindirect_one)[i] = 0;
		}
		testfs_free_block_from_inode(in, in->in.i_dindirect);
		in->in.i_dindirect = 0;
	}

	in->in.i_size = 0;
	in->i_flags |= I_FLAGS_DIRTY;
	return 0;
}
