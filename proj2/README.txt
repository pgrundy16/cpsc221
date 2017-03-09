README.txt

Name:         Eduardo Garza
Server ID:    r1v0b
Student ID:   60002152
Class:        CPSC 221
Lab Section:  L2F

Title:    Project 2 | Word Frequency using Trees and Heaps

Reference Code : 
  I would like to reference the Unit #2 Slide-Set on Priority
    Queues and Heaps as I took the idea to implement my heap
    functions similar to how they did it for the Min-Heap.
  http://www.ugrad.cs.ubc.ca/~cs221/current/handouts/lectures/lec02_ed.pdf

+===============================================================+
                  Instructions for Marker
+===============================================================+

Note: The testing that I completed for all required sections is labeled, 

  cout << "\n ++ Eduardo Testing ++\n" << endl;
  
  <... code ... > 

  cout << "\n ++ End of Eduardo Testing ++\n" << endl;

        ... so that at the console it is clear which tests I wrote and which 
        tests were already implemented.


i. Part 1A : Implement of Insert & Testing

  My tests for Part 1A insert elements {1000, 1500, 2000, and 2500 }
    because as each one of these elements is added, it will be the 
    greatest 'freq' value in the Max-Heap so it will not require any 
    swaps. 
  
  In addition, it will be evident that it works as when we print the top
    element after each new insertion, the new el. should be the top val. 
  
  To reuse the same heap, I then delete all elements by calling delete_max()
    four times.

  Then I insert {45, 35, 25} in order because it show 45 as the top each time
    and the others will be swapped down to their correct positions as 
    children to the root node.


ii. Part 1B : Implement Delete & Testing
  
  My tests for Part 1B declare a new Max-Heap sized-10 and insert
    elements {1000, 1500}, and print the top after each insertion.

  Then we delete once and expect 1000 to be the top.

  Finally, we add {800, and 900} so that the tree will have 1000
    as root, 800 and left, and 900 and right nodes. This will be the 
    expected outcome after the correct swap_down operations.

  Then we delete all nodes. And try to delete once more when the Heap is
    empty and it returns the exception letting us know that it is empty.


ii. Part 2 : Implement BST Word_Frequency & Testing
  
  My tests including adding the following name string-items:

    string_bst test;
    test.insert("daniel");
    test.insert("carlos");
    test.insert("beto");
    test.insert("albert");
    test.insert("daniel");
    test.insert("daniel");

  Then using word_frequency() we test that we can find "daniel"
    and "david", where "daniel" will return 3 and "david" return 0.


iii. Part 3 : Implementation of Analysis Functions & Testing

  For Part 3, I wanted to use the same MaxHeap hp that is passed
    to all 3 functions that I implemented. As they were passed by 
    reference and I did not want to copy them completely, I did the 
    following:

    1. Created a holder[] array that stores the top 5.

    2. Created a necessary[] array that holds all the elements 
      that are 'poped-off'/deleted (because when you want to look
      at more than one element in the Heap you must delete them).

    3. Checks the condition that is asked for:

        if (str.len >= desired_length) OR
        if (str[0] == desired_char)

    4. Prints, at most, the top 5 of a condition.

    5. Re-inserts all the deleted elements to the Heap to preserve
      its initial size.


+===============================================================+
                          HOW TO RUN
+===============================================================+
1. The program will already compiled but if you want to make 
  sure that it works you can compile it like this:

  make 

2. Then run the program:

  ./main

3. All the standard output can be found in a file called:

  output.txt

+===============================================================+
                          End of README
+===============================================================+
