time_t begin;
    time_t end;
    
    //allocate memory for result

    result = (PPMPixel*) malloc(sizeof(PPMPixel) * w * h);
    printf("Work per thread: %i\n", indWork);
    
    int count = 0;

    time(&begin);
    for(int i = 0;i < THREADS;i++){
    //allocate memory for parameters (one for each thread)

        toThreads[i] = (struct parameter*) malloc(sizeof(struct parameter));
    /*create threads and apply filter.
     For each thread, compute where to start its work.  Determine the size of the work. If the size is not even, the last thread shall take the rest of the work.
     */
        toThreads[i]->image = image;
        toThreads[i]->result = result;
        toThreads[i]->h = h;
        toThreads[i]->w = w;
        toThreads[i]->start = i * indWork;
        toThreads[i]->size = indWork;
        ///*
        if(pthread_create(&threads[i], NULL, threadfn, (void*) toThreads[i]) != 0){
            fprintf(stderr ,"error number at thread");
            exit(1);
        }


    }
   

   //Let threads wait till they all finish their work.

    time(&end);
    *elapsedTime = difftime(end, begin);
    printf("begin: %ld\t End: %ld\n",begin, end);
    printf("Elapsed time: %F\n", *elapsedTime);