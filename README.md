# ft_contrast
A multi-thread processing project

### About this project
* This is a Rushes project at [École 42](https://42.fr)
* Rushes project is a 2 days group project on weekend incremented to a normal school curriculum.
* My teammate is [amarandi](https://github.com/madriane)
* The objective of this project is to create a multi-thread processing library.
* The project divided into 3 parts
    * ft_contrast: create a program to change the contrast of .pgm photo
    * ft_contrast_th: rewrite ft_contrast to, make it multi-thread processing
    * ft_contrast_tp: rewrite ft_contrast_tp, make the library that handle multi-thread processing (threadpool) and use this library with the program

### Remark
* We did all 3 parts but we wrongly interpreted the subject so we handed in just the best part of our work (which is ft_contrast_tp) as ft_contrast. As a result, you can only find one part of it.
* The program hasn't been handled the memory leaks.

### How to run the program
Run make command
```
make
```

To run the program
```
./ft_contrast -f [input file] -c [contrast level 0-100] -o [output file]
```

For example,
* input file: ~/Documents/input.pgm
* output file: ~/Documents/output.pgm
* contrast level: 40
```
./ft_contrast -f ~Documents/input.pgm -c 40 -o ~Documents/output.pgm
```

### The idea behind the project
For the first part, ft_contrast, my teammate made it. He used get_next_line function (from my [libft](https://github.com/terngkub/libft)) to read the input line by line. Then at each line, he split each pixel, convert them to integer, changes the contrast, converts them back to string and writes them to the output. The program worked well with the small photo but it took too long for the big picture (1GB). So I optimized it by changing the get_next_line to read and lseek functions which speed things up a lot.

For the second part, I used the pthread library to make the thread pool. First, I created threads with pthreads_create. Each thread will run callback function which is while loop doing the calculation job when it gets the condition signal from the main thread (using pthread_cond_wait function). The main thread will read the input and enqueue the data to the list. Then it sends the signal to the threads using pthread_cond_signal function. When main thread finished the reading, it waits for the threads to finish with pthread_join. Finally, when every thread finishes working, the program writes the output and we get a new contrast photo.

For the third part, I create structures to represent thread pool and task queue. A thread pool contains every information necessary to do the job. A task queue contains a function pointer and data. When we run the program, it runs tp_exec_queue_add which will add task to the thread pool. When a thread is ready to do the job, it runs the function from function pointer with the data. In this way, you can change the task job as you want by changing a function pointer and data.

### My thought about this project
The subject of this project is very interesting. We can increase the speed of the process by implementing multi-thread processing. I think that this skill will be useful in the future even if it isn't in C language.

Somehow, I had a difficulty with this project. The project is quite a rush as its name implies. We only have 2 days to do it and multi-thread processing is new to us and it isn't a little subject so it took time to learn. Moreover, my teammate also did another project alongside with this one so he didn't have time to fully contribute to this project. It about 20% his and 80% mine. 

In the end, even if we didn't hand in all three parts, all the correctors understand that (actually the third part contains all the previous parts) and we managed to get 117/100 (17 for the bonus) for this project. Thank you to my teammate who communicated and explained to the correctors in French.
