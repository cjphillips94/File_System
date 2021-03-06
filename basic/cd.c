﻿#include "../include/fs.h"

int cd()
{
  bool from_root = FALSE;

  if (!out[1] || strcmp(out[1], "/") == 0) { // Changing to home directory
    iput(running->cwd);
    running->cwd = iget(root->dev, root->ino);
    return 0;
  }
  if (strcmp(out[1], ".") == 0) {    // No need to change directory
    return 0;
  }
   
  char *base = basename(out[1]);  // target directory
  char buf[BLKSIZE];
  int i = 0, ino, dev = running->cwd->dev;
  MINODE *mip = 0;

  if(out[1][0] == '/')
  {
    dev = root->dev;
    //mip = iget(dev, root->ino);
  }
  /*
  else
  {
    mip = iget(dev, running->cwd->ino);
  }
  */

  if (out[1][0] == '/')
  {
    from_root = TRUE;
  }

  ino = get_inode(out[1], &dev, FALSE);
  if (ino < 0)
  {
    return -1;
  }
  mip = iget(dev, ino);
  if ((mip->Inode.i_mode & 0xF000) != 0x4000)
  {
    printf("Not a directory.\n");
    iput(mip);
    return -2;
  }

  iput(running->cwd);
  running->cwd = mip;

  /*
  numTokens = tokenize(out[1], "/");
  if(from_root)
    numTokens--;
  
  while(i < numTokens) {
    if (i < (numTokens - 1) && !S_ISDIR(mip->Inode.i_mode)) 
    {
      printf("\"%s\" : Not a directory\n", out[i]);
      if(mip != root && mip != running->cwd)
      {
        iput(mip);
      }
      return -2;
    }

    ino = search(mip, out[i]);

    if(ino < 0) // Inode not found
    { 
      printf("\"%s\" : Does not exist.\n", out[i]);
      iput(mip);
      return -1;
    }

    iput(mip);
    
    mip = iget(mp->dev, ino);
    i++;
  }

  if (!S_ISDIR(mip->Inode.i_mode)) { // not a directory
    printf("\"%s\" : Not a directory.\n", base);
    return -3;
  }
  */

  //running->cwd = mip;
    
  return 0;
}