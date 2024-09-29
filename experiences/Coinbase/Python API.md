Solve these in Python

Level 1 - Initial Design & Basic Functions 

• FILE_UPLOAD(file_name, size) 
• Upload the file to the remote storage server 
• If a file with the same name already exists on the server, throws a runtime exception 

• FILE_GET (file_name) 
• Returns size of the file, or nothing if the file doesn't exist 

• FILE_COPY (source, dest) 
• Copy the source file to a new location 
• If the source file doesn't exist, throws a runtime exception 
• If the destination file already exists, overwrites the existing file

Level 2 - Data Structures & Data Processing 

• FILE_SEARCH (prefix) 
Find top 10 files starting with the provided prefix. Order results by their size in descending order, and in case of a tie by file name.

Level 3 - Refactoring & Encapsulation 

Files now might have a specified time to live on the server. 
Implement extensions of existing methods which inherit all functionality but also with an additional parameter to include a timestamp for the operation, and new files might specify the time to live - no til means lifetime being infinite. 

• FILE_UPLOAD_AT(timestamp, file_name, file_size) 
• FILE_UPLOAD_AT(timestamp, file_name, file_size, ttl) 
    • The uploaded file is available for ttl seconds. 
• FILE_GET_AT (timestamp, file_name) 
• FILE_COPY_AT(timestamp, file_from, file_to) 
• FILE_SEARCH_AT(timestamp, prefix) 
• Results should only include files that are still "alive" 

Level 4 - Extending Design & Functionality ROLLBACK (timestamp) 
• Rollback the state of the file storage to the state specified in the timestamp 
• All ttls should be recalculated accordingly
