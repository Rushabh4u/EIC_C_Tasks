
/*  Author: P. SUBHASH CHANDRA BOSE
 *  Created: 12 November, 2024
 *  Modified: 17 November 2024 */


/*INCLUDED HEADER FILES*/
#include "simplefs-ops.h"

extern struct filehandle_t file_handle_array[MAX_OPEN_FILES]; // Array for storing opened files


/*create(char *filename) function which creates a file*/
int simplefs_create(char *filename)
{
   

    
    struct inode_t *inodeptr = (struct inode_t*)malloc(sizeof(struct inode_t));
    
    /*If the file with filename already exists then return -1,not considering that case*/
    for(int inode_num=0;inode_num<NUM_INODES;inode_num++)
    {
	    simplefs_readInode(inode_num,inodeptr);
        
      	    if(strcmp(inodeptr->name,"filename")==0)
	    {
	    

		    fprintf(stderr,"File already exists");
		    return -1;
	    
	    
	    }
    

    }



    /*Create file with name `filename` from disk*/
     
     int inode_num = simplefs_allocInode();     /*Iam getting the inode number from freelisted inodes from superblock structure and 
						  writing that inode as in use*/


     if(inode_num==-1)
     {
     
          fprintf(stderr,"There is no free inode present\n");
          
	  return -1;
     
     }

     struct inode_t *inode = (struct inode_t*)malloc(sizeof(struct inode_t));

     /*updating the values in the inode of struct type inode_t */
     inode->status= INODE_IN_USE;
     strcpy(inode->name,filename);
     inode->file_size = 0;
     
     for(int i=0;i<MAX_FILE_SIZE;i++)
     {
          
	     inode->direct_blocks[i] = -1;
     
     
     }

     /*Here iam writing the samething to inode with allocated inode_num and inode structure*/
    simplefs_writeInode(inode_num,inode);

     return inode_num;   /*Finally returning the inode number*/

     free(inode);

     free(inodeptr);

     return 0;


}



/*simplefs_delete(char *filename)  deletes the file with filename from disk*/
void simplefs_delete(char *filename)
{
    
      
    /*Error handling*/

    if(filename == NULL)
    {

             fprintf(stderr,"Invalid parameters\n");

             return ;

    }


   struct inode_t *inodeptr = (struct inode_t*)malloc(sizeof(struct inode_t));

   int inodenum;
   int found =0;


   /*For finding the inodenumber with filename "filename"*/
   for(inodenum=0;inodenum<NUM_INODES;inodenum++)
   {
          simplefs_readInode(inodenum,inodeptr);

         if(strcmp(inodeptr->name,filename)==0)
	 {
	 
            
                  found = 1;
		  break;

         }       	 
   
   }

   if(found ==0)
   {
     
	   fprintf(stderr,"The inode not found\n");
   
   
   }


   /*Iterating through 4 data blocks and freeing them*/
   for(int i = 0 ; i < 4; i++)
   {
	if(inodeptr->direct_blocks[i] != -1)     /*If the corresponding blocks are allocated then free them*/
	{

   		simplefs_freeDataBlock(inodeptr->direct_blocks[i]);
   	}

   }
  
   simplefs_freeInode(inodenum);  /*We have found the inodenum , then here we are freeing that inode with this function call*/
    

   free(inodeptr);
    

}



/*simplefs_open(char *filename) opens the file with 'filename'*/
int simplefs_open(char *filename)
{
    
     /*Error handling*/
     if(filename == NULL)
     {
         
	     fprintf(stderr,"Invalid parameters\n");

	     return -1;
     
     }



     struct inode_t *inodeptr = (struct inode_t*)malloc(sizeof(struct inode_t));
      
   
      int inodenum;
  
      int found =0;                                                 /*Find the inode number corresponding to the filename*/

   for(inodenum=0;inodenum<NUM_INODES;inodenum++)
   {
           /*reading from disk to inodeptr structure*/
	   simplefs_readInode(inodenum,inodeptr);

     	   if(strcmp(inodeptr->name,filename)==0)
         {

              found=1;

              break;
         }

       

   }

   free(inodeptr);

   if(found==0)
   {

           fprintf(stderr,"There is no file with the entered name\n");
           return -1;

   }

   
   /*Iterating through the file_handle_array with limit of MAX_OPEN_FILES*/   
   for(int file_handle=0;file_handle<MAX_OPEN_FILES;file_handle++)
   {
   
        if(file_handle_array[file_handle].inode_number == -1)
	{
	
	       /*Assigning our found inodenum to the file_handle_array[] and finally returning the filehandle*/
	       file_handle_array[file_handle].inode_number = inodenum;

	       return file_handle;
	
	
	}

   
   }
   
   /*If no filehandle is free*/

      fprintf(stderr,"No filehandle is free\n");
   
      return -1;    
  

}





/* simplefs_close(int file_handle) ,closes file pointed by `file_handle`*/
void simplefs_close(int file_handle)
{
   
    
     /*We have file_handle as a parameter if we manipulate that corresponding structure of filehandle array offset and inode number
      * we can close the file*/
   


        /*Error handling*/	
        if(file_handle<0 || file_handle > MAX_OPEN_FILES)
	{
	    
		fprintf(stderr,"Invalid file_handle\n");
	
	
	}	



	file_handle_array[file_handle].offset = 0;
	file_handle_array[file_handle].inode_number = -1;



}



/*simplefs_read(int file_handle, char *buf, int nbytes) ,read `nbytes` of data into `buf` from file pointed by `file_handle` starting at current offset*/
int simplefs_read(int file_handle, char *buf, int nbytes)
{
    
   

      /*Error handling*/  
      if(file_handle<0 || file_handle > MAX_OPEN_FILES || nbytes <=0)
      {
          
	  fprintf(stderr,"Invalid parameters\n");
	  return -1;
      
      
      }

      int inodenum;

      /*Getting inode_number to variable inodenum*/
      inodenum = file_handle_array[file_handle].inode_number;


      char tempbuf[BLOCKSIZE];

      struct inode_t *inodeptr = (struct inode_t*)malloc(sizeof(struct inode_t));
      
      if(inodeptr == NULL)
      {
      
         fprintf(stderr,"Memory allocation failed\n");
	 return -1;
      
      }

      /*Reading from disk to inodeptr structure*/
      simplefs_readInode(inodenum,inodeptr);
      

      int offset = file_handle_array[file_handle].offset;

      int filesize = inodeptr->file_size;

      if(nbytes+offset > filesize)
      {
      

	    fprintf(stderr,"Trying to read beyond the filesize\n");  

            free(inodeptr);
            return -1;
      
      }

      
      int bytes_remaining = nbytes;   /*Bytes remaining to read*/

      int bytes_read = 0;   /*Read bytes , tracking how many bytes read*/

      int block_index = offset/BLOCKSIZE;    /*To get initial block_index*/

      int block_offset = offset%BLOCKSIZE;   /*To get the offset in the first block*/


      int bytes_to_read;   /*bytes to read in single block*/


      while(bytes_remaining > 0)
      {
             
             bytes_to_read = BLOCKSIZE - block_offset;
             
	     if(bytes_to_read > bytes_remaining)
	     {
	     
	          bytes_to_read = bytes_remaining;

	     }
	     simplefs_readDataBlock(inodeptr->direct_blocks[block_index], tempbuf);   /*Storing readbytes from particular block into tembuf*/

             memcpy(buf+bytes_read ,block_offset + tempbuf, bytes_to_read);/*memcpy() the things from tempbuf to buf*/

		  
	     
	          /*Updating the counters*/

		  block_index++;
		  block_offset = 0;
		  bytes_read = bytes_read + bytes_to_read;
		  bytes_remaining = bytes_remaining - bytes_to_read;

      
      }

    
    free(inodeptr);
    return 0;



}



/*simplefs_write(int file_handle, char *buf, int nbytes), write `nbytes` of data from `buf` to file pointed by `file_handle` starting at current offset*/
int simplefs_write(int file_handle, char *buf, int nbytes)
{
   

    /*Error handling*/
    if(file_handle<0 || file_handle > MAX_OPEN_FILES)
    {
    
        fprintf(stderr,"Invalid parameters at Write\n");
	return -1;

    
    }

    int inodenum ;
    int offset;

    inodenum = file_handle_array[file_handle].inode_number;
    offset = file_handle_array[file_handle].offset;

    char tempblock[BLOCKSIZE];

    struct inode_t *inodeptr = (struct inode_t*)malloc(sizeof(struct inode_t));
    
    if(inodeptr == NULL)
    {

         fprintf(stderr,"Memory allocation failed\n");
         return -1;

    }

    if(nbytes+offset > BLOCKSIZE*MAX_FILE_SIZE)
    {
    
       fprintf(stderr,"Cannot write more than 256 bytes\n");
       return -1;
    
    }

    /*Reading from disk to inodeptr structure*/
    simplefs_readInode(inodenum,inodeptr);
    
    int bytes_remaining = nbytes;   /*Bytes remaining to write into the file*/

    int bytes_write = 0;        /*Bytes written to the file, initialised to 0*/

    int buff_offset = 0;       /*buff_offset initialised to 0, from where we gonna read and write that into the file*/
    

    int block_index = offset/BLOCKSIZE;   /*The intial block index*/

    int block_offset = offset%BLOCKSIZE;  /*The offset in that particular block*/

    int block_offset_to_EOB = BLOCKSIZE - block_offset; /*This is the bytes to write to the End of the block*/

    /*file_size holds the file offset value*/
    inodeptr->file_size = offset;


    int temp_blocknum;
    int blocks_allocated[MAX_FILE_SIZE];
    int block_count =0;

    while(bytes_remaining > 0)
    {
         
	   
            
           if(bytes_remaining < block_offset_to_EOB)
	   {
	   
                   bytes_write = bytes_remaining;
	   
	   }


	   else
	   {
	   
	           bytes_write = block_offset_to_EOB;
	   
	   
	   }
         
	   /*If the block is not allocated*/
         if(inodeptr->direct_blocks[block_index] == -1)
	 {
	 
	        temp_blocknum = simplefs_allocDataBlock();


		if(temp_blocknum == -1)
		{
		
		       for(int i=0;i<block_count;i++)
		       {
		       
		            simplefs_freeDataBlock(blocks_allocated[i]);
		       
		       }

		       return -1;
		
	
		}


		inodeptr->direct_blocks[block_index] = temp_blocknum;
		blocks_allocated[block_count++] = temp_blocknum;

		memcpy(tempblock+block_offset,buf+buff_offset,bytes_write);

		inodeptr->file_size += bytes_write;
	        
	        simplefs_writeDataBlock(inodeptr->direct_blocks[block_index],tempblock);	
	 
	
	 }

	 /*If the block is already allocated and some data is there in it */
	 else
	 {
	 
	        simplefs_readDataBlock(inodeptr->direct_blocks[block_index],tempblock);
		memcpy(tempblock+block_offset,buf+buff_offset,bytes_write);

		inodeptr->file_size += bytes_write;

		simplefs_writeDataBlock(inodeptr->direct_blocks[block_index],tempblock);
	 
	 
	 }


	   /*Incrementing and decrementing counters accordingly*/
           

           block_index++;
           block_offset = 0;

           buff_offset += bytes_write;

	   block_offset_to_EOB = BLOCKSIZE - block_offset;

           bytes_remaining = bytes_remaining - bytes_write;
           

    
    
    }

    /*Writing the changes to inode with   "simplefs_writeInode(inodenum,inodeptr)"*/
    simplefs_writeInode(inodenum,inodeptr);
    
    free(inodeptr);

    return 0;


}



/* simplefs_seek(int file_handle, int nseek), function  increase `file_handle` offset by `nseek'*/
int simplefs_seek(int file_handle, int nseek)
{
 
     struct inode_t* inodeptr = (struct inode_t*)malloc(sizeof(struct inode_t));

     /*Reading from disk to inodeptr*/
     simplefs_readInode(file_handle_array[file_handle].inode_number,inodeptr);	     
     
     /*Error handling*/
     if(file_handle < 0 || file_handle >= MAX_OPEN_FILES)
     {
     
          fprintf(stderr,"Invalid filehandler\n");
	  return -1;
     
     }

     /*Error handling*/
     if(nseek > inodeptr->file_size - file_handle_array[file_handle].offset || nseek < -(file_handle_array[file_handle].offset))
     {
          
             fprintf(stderr,"Invalid nseek value\n");
	     return -1;
     
     }
     

     /*Incrementing the file offset value with adding the nseek number */
     file_handle_array[file_handle].offset += nseek;     
     
     free(inodeptr);
     return 0;



}
