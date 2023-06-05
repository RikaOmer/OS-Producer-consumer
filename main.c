

// create dynamic array

// producer(int i, int numProducts, int queueSize){
    // create a new bounded queue with size queueSize
    // for (i = 0; i < numProducts; i++) {
        // create a new product
        // enqueue the product
    // }
    // enter DONE into the queue
    
//}
// for (i = 0; i < N; i++) { 
    // read from the input file the number of products and the queue size
    // pthred producer(i, numProducts, queueSize);
// }

 // sportquere = new unbounded queue
 // newsquere = new unbounded queue
 // weatherquere = new unbounded queue

// dispatcher(){
    // while (true) {
        // int count = 0;
        // for (i = 0; i < N; i++) {
            // if (count == N) {
                // sportquere.enqueue("DONE");
                // newsquere.enqueue("DONE");
                // weatherquere.enqueue("DONE");
                // return;
            // lock the mutex for the bounded queue
            // char* element = array[i].dequeue();
            // if (element == NULL) {
                // continue;
            // }
            // unlock the mutex
            // lock the mutex for the unbounded queue
            // if (element == DONE) {
                // destroy the bounded queue
                // count++;
                // continue;
            // }
            // if (element == SPORT) {
                // sportquere.enqueue(element);
            // }
            // if (element == NEWS) {
                // newsquere.enqueue(element);
            // }
            // if (element == WEATHER) {
                // weatherquere.enqueue(element);
            // }
        // }
    // }

    // thrhead dispatcher

    // mixedquere = new bounded queue(size = CO_EDITOR_QUEUE_SIZE)

    //sportCoEditor(sportquere){
        // count = 0;
        // while (count < 3) {
            // lock the mutex for the unbounded queue
            // char* element = sportquere.dequeue();
            // if (element == NULL) {
                // continue;
            // }
            // unlock the mutex
            // if (element == DONE) {
                // mixedquere.enqueue("DONE");
                // count++;
                // destroy the unbounded queue
                // return;
            // }
            // lock the mutex
            // mixedquere.enqueue(element);
            // unlock the mutex
        // }
    //newsCoEditor(newsquere){
        // while (true) {
            // lock the mutex for the unbounded queue
            // char* element = newsquere.dequeue();
            // if (element == NULL) {
                // continue;
            // }
            // unlock the mutex
            // if (element == DONE) {
                // mixedquere.enqueue("DONE");
                // destroy the unbounded queue
                // return;
            // }
            // lock the mutex
            // mixedquere.enqueue(element);
            // unlock the mutex
        // }
    //weatherquereCoEditor(weatherquere){
        // while (true) {
            // lock the mutex for the unbounded queue
            // char* element = weatherquere.dequeue();
            // if (element == NULL) {
                // continue;
            // }
            // unlock the mutex
            // if (element == DONE) {
                // mixedquere.enqueue("DONE");
                // destroy the unbounded queue
                // return;
            // }
            // lock the mutex
            // mixedquere.enqueue(element);
            // unlock the mutex
        // }

        //thread screenManager(mixedquere){
            // int count = 0;
            // while (count < 3) {
                // lock the mutex for the bounded queue
                // char* element = mixedquere.dequeue();
                // if (element == NULL) {
                    // continue;
                // }
                // unlock the mutex
                // if (element == DONE) {
                    // count++;
                    // return;
                // }
                // print the element
            // }

//     PRODUCER 1
// [number of products]
// queue size = [size]


// PRODUCER 2
// [number of products]
// queue size = [size]

// …
// …
// …
// PRODUCER n
// [number of products]
// queue size = [size]

// Co-Editor queue size = [size]

#define PRODUCER_NUM 10;
#define CO_EDIROT_NUM 3;