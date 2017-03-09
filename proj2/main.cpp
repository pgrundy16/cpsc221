#include <iostream>

#include "string_bst.hpp"
#include "max_heap.hpp"
#include "text_item.hpp"
#include "util.hpp"

using namespace std;


//--- PART 1A: Implementation and testing of heap insert
void heap_insert_tests(max_heap &hp) {
	text_item temp;
	std::string word = "item";
	int random_num;
	long int seed = long(time(0));    // seed for random number generator
	srand(seed);
	
	//--- Testing insert functionality
	std::cout << "*** TESTING INSERT ***" << std::endl;
	//--- This adds 5 items to the heap with random numbers
	//    and prints out the top, but it does not fully 
	//    test the correctness of the insert function.
	for (int i = 0 ; i < 5; i++) {
		random_num = rand() % 100;
		string text = word;
		text += std::to_string(i+1);
		std::cout << "adding " << text << ",  with number " << random_num << " to heap" << std::endl;
		hp.insert(text_item{text, random_num});	
		temp = hp.top();
		std::cout << "Top of heap is: " << temp << std::endl;		
	}
	
	//--- Specific insert functionality that should be tested:
		
	max_heap h2(10);

	cout << "\n ++ Eduardo Testing ++\n" << endl;

	// insert without any swap_ups needed
	
	h2.insert(text_item{"New", 1000 });
	std::cout << "Top of heap is: " << h2.top() << std::endl;		

	h2.insert(text_item{"New", 1500 });
	std::cout << "Top of heap is: " << h2.top() << std::endl;		

	h2.insert(text_item{"New", 2000 });
	std::cout << "Top of heap is: " << h2.top() << std::endl;		

	h2.insert(text_item{"New", 2500 });
	std::cout << "Top of heap is: " << h2.top() << std::endl;		

	h2.delete_max();
	h2.delete_max();
	h2.delete_max();
	h2.delete_max();

	// insert with a swap_up / multiple swap_ups
		// <INSERT TEST(S) HERE>
	h2.insert(text_item{"New", 45 });
	std::cout << "Top of heap is: " << h2.top() << std::endl;		

	h2.insert(text_item{"New", 35 });
	std::cout << "Top of heap is: " << h2.top() << std::endl;		

	h2.insert(text_item{"New", 25 });
	std::cout << "Top of heap is: " << h2.top() << std::endl;		

	cout << "\n ++ End of Eduardo Testing ++\n" << endl;

}

//--- PART 1B: Implementation and testing of heap delete
void heap_delete_tests(max_heap &hp) {
	text_item temp;
	
	//--- Testing deleteMax functionality
	std::cout << "*** TESTING DELETEMAX ***" << std::endl;
	//--- This does not fully test delete_max functionality.
	if (hp.size() > 1) {
		temp = hp.delete_max();
		std::cout << "Item returned from heap delete: "<< temp << std::endl;
		temp = hp.top();
		std::cout << "Top of heap is now: " << temp << std::endl;	
	}
	
	//--- Specific insert functionality that should be tested:
		
	max_heap h2(10);

	cout << "\n ++ Eduardo Testing ++\n" << endl;

	// remove_max works when swap_down with left child
		// <INSERT TEST(S) HERE>
	h2.insert(text_item{"New", 1000 });
	std::cout << "Top of heap is: " << h2.top() << std::endl;		

	h2.insert(text_item{"New", 1500 });
	std::cout << "Top of heap is: " << h2.top() << std::endl;		
	
	/* Delete Expected */
	std::cout << "Deleted top" << endl;
	h2.delete_max();
	std::cout << "Expected Top: 1000" << endl;
	std::cout << "Top of heap is: " << h2.top() << "\n" << std::endl;		

	// remove_max workd when swap_down with right child
	h2.insert(text_item{"New", 800 });
	std::cout << "Top of heap is: " << h2.top() << std::endl;		

	h2.insert(text_item{"New", 900 });
	std::cout << "Top of heap is: " << h2.top() << std::endl;		
	
	/* Delete Expected */
	std::cout << "Deleted top" << endl;
	h2.delete_max();
	std::cout << "Expected Top: 1000" << endl;
	std::cout << "Top of heap is: " << h2.top() << "\n" << std::endl;		

	// remove_max on an empty heap (should throw exception similar to top())
	while(!h2.empty())
		h2.delete_max();

	/* Empty, and try again. */
	// h2.delete_max();	

	cout << "\n ++ End of Eduardo Testing ++\n" << endl;
		
}

//--- PART 2: Implementation and testing of BST word_frequency
void tree_tester(string_bst const &tree) {
	std::cout << std::endl << "BEGINNING TESTS FOR PART 2" << std::endl;
	
	//--- Testing word_frequency functionality
	//--- This does not fully test word_frequency functionality.
	if (tree.size() > 1) {
		string to_find = "difficult";
		int num_times = tree.word_frequency(to_find);
		std::cout << "Found: "<< to_find << 
			" in the input file " << num_times 
			<< " time(s)." << std::endl;
	}
	
	//--- Specific insert functionality that should be tested:

	cout << "\n ++ Eduardo Testing ++ \n" << endl;
	
	// can search through both left and right subtrees if not found at current node
	string_bst test;
	test.insert("daniel");
	test.insert("carlos");
	test.insert("beto");
	test.insert("albert");
	test.insert("daniel");
	test.insert("daniel");

	/* What is the freq of 'daniel'? */
	std::cout << "Searching for 'daniel': Expected freq return is 3. " << endl;
	std::cout << "Word 'daniel' Freq: " << test.word_frequency("daniel") << "\n" << endl;	
		
	// returns 0 if word is not found
	/* What is the freq 'david'? */
	std::cout << "Searching for 'david': Expected freq return is 0. " << endl;
	std::cout << "Word 'david' Freq: " << test.word_frequency("david") << "\n" << endl;	
			
	cout << "\n ++ End of Eduardo Testing ++\n" << endl;
}

//--- PART 3: Implementation and testing of word frequency analysis
void overall_most_freq(max_heap hp) {
	std::cout << "*** Top 5 most frequent words: ***" << std::endl;

	//--- Add your code to print out the 5 most frequent words below:
	if (hp.size() > 1) {
		std::cout << "Most frequent text item: " << hp.top() << std::endl;
		
		int size = hp.size();
		text_item holder[5];

		for(int i=0; i < size; i++)
		{
			/* Iterate, at most, 5 times */
			if(i == 5) break;

			/* Store each el., then delete it. */
			holder[i] = hp.top();
			hp.delete_max();
		}

		/* Print out the top 5. */
		for(text_item e : holder) {
			cout << "Item: " << e.word << " and freq: "
				<< e.freq << "." << endl;
			
			/* Add top 5 back to max-heap. */
			hp.insert(e);
		}
	}

}

void at_least_length(max_heap hp, size_t num_letters) {
	cout << "*** Top 5 most frequent words with at least " 
		<< num_letters << " letters ***" << std::endl;
		
	//--- Add code to print out the 5 most common
	//--- words of length at least <num_letters>
		
	int size = hp.size();
	int h_count = 0, n_count = 0;
	text_item holder[5];
	text_item necessary[size];

	for(int i=0; i < size; i++)
	{
		/* Iterate, at most, 5 times */
		if(h_count == 5) break;

		/* Store each el., then delete it. */
		text_item temp = hp.top();

		/* Store all items here. */
		necessary[n_count++] = temp;

		/* Check for desired str len. */
		if(temp.word.length() >= num_letters) {
			holder[h_count++] = temp;
		}

			/* Pop item and move to next. */
			hp.delete_max();
	}

	/* Print out the top 5. */
	for(int i = 0; i < h_count; i++) {
		cout << "Item: " << holder[i].word << " and freq: "
			<< holder[i].freq << "." << endl;
	}

	/* Add all items back to heap. */
	for(int i = 0; i < n_count; i++) {
		hp.insert(necessary[i]);
	}
	
}

void starts_with(max_heap hp, char starts_with_letter) {
	cout << "*** Top 5 most frequent words that begin with " 
		<< starts_with_letter << " ***" << std::endl;
		
	//--- Add code to print out the 5 most common words
	//--- that start with the letter <starts_with_letter>

	int size = hp.size();
	int h_count = 0, n_count = 0;
	text_item holder[5];
	text_item necessary[size];

	for(int i=0; i < size; i++)
	{
		/* Iterate, at most, 5 times */
		if(h_count == 5) break;

		/* Store each el., then delete it. */
		text_item temp = hp.top();

		/* Store all items here. */
		necessary[n_count++] = temp;

		/* Check for desired str len. */
		if(temp.word[0] == starts_with_letter) {
			holder[h_count++] = temp;
		}

			/* Pop item and move to next. */
			hp.delete_max();
	}

	/* Print out the top 5. */
	for(int i = 0; i < h_count; i++) {
		cout << "Item: " << holder[i].word << " and freq: "
			<< holder[i].freq << "." << endl;
	}

	/* Add all items back to heap. */
	for(int i = 0; i < n_count; i++) {
		hp.insert(necessary[i]);
	}	
}

void heap_tester() {	
	text_item temp;
	int heap_size = 10; //feel free to create heaps of other sizes when testing
	//cout << "How many items should be added to heap? ";
	//cin >> heap_size;
	max_heap hp(heap_size);
	std::cout << "Created heap of size " << heap_size << std::endl;
		
	//--- Testing heap size and top
	std::cout << "Current number of items in heap is: " << hp.size() << std::endl;
	try {
		temp = hp.top(); //should throw and exception without items in heap
		std::cout << "Top of heap is: " << temp << std::endl;	
	} catch (std::logic_error e) {
		std::cout << e.what() << std::endl;
	}
	// PART 1A:
	std::cout << std::endl << "BEGINNING TESTS FOR PART 1A" << std::endl;
	heap_insert_tests(hp);
	

	// PART 1B:
	std::cout << std::endl << "BEGINNING TESTS FOR PART 1B" << std::endl;
	heap_delete_tests(hp);

}

void text_analysis_tester(string_bst &tree) {
	std::cout << std::endl << "BEGINNING TESTS FOR PART 3" << std::endl;
	overall_most_freq(copy_to_heap(tree));
	std::cout << std::endl;
	at_least_length(copy_to_heap(tree), 8); // change the 8 to test other string-lengths
	std::cout << std::endl;
	starts_with(copy_to_heap(tree), 'c'); // change the 'c' to test words that starts_with_letter
											// with different characters
}

/* Main Function. */
int main(int argc, char* argv[]) {
	
	//--- Part 1: max_heap implementation
	heap_tester(); 

	//--- Part 2: string_bst implementation
	string_bst tree;
	load_bst("sample1.txt", tree); // create a bst from an input file.
	tree_tester(tree);			//sample2.txt contains a much bigger file
	
	//--- Part 3: word frequency analysis of text files
	text_analysis_tester(tree);

	/* Part 3: Part 2 */
	string_bst t2;
	load_bst("sample2.txt", t2);
	tree_tester(t2);

	text_analysis_tester(t2);

}
