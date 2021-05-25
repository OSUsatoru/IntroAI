#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>
#include <typeinfo>
#include <algorithm>
#include <cctype>


using namespace std;

/* 	for step1
	somewhere create vector<vector<string>> preprocess
	( easy to pushback by using string )

	1. getline to store string by line
	2. convert each string to proper words (e.g. no punctuation)
	3. store all vocab in one vector (without classLabel)
	5. sort and uniqu to erace duplicated words
	--------------------------------------------------
	create bocabulary first!

	6. for each string from (1.),
*******************************************/
/*
 * This struct represents a sentence
 * 'text' being the text the sentence has
 * 'classLabel' either being 1 (positive) or 0 (negative)
 *
*/
struct sentence
{
	vector<string> text;
	int classLabel;
};
vector<string> split(const string &str, char sep);
void readFile(char *in_file, vector<sentence> &v );
void proper_word(vector<string> &text);
void create_vocabulary(vector<sentence> &trainingSet, vector<string> &vocabulary);
void convert_process(vector<sentence> &sentenceSet, vector<string> &vocabulary, vector<vector<string>> &converted_sentenceSet);
void classification();

/*
	argv[1] is the
***********************************/
int main(int argc, char *argv[])
{
	vector<sentence> testSet, trainingSet;
	vector<string> vocabrary;

	char testText[] = "testSet.txt", trainingText[] = "trainingSet.txt";
	char test_out[] = "preprocessed_test.txt", training_out[]="preprocessed_train.txt";

	/* Get the data into testSet and trainingSet */
	readFile(testText, testSet);
	readFile(trainingText, trainingSet);
	/* Create feature vector */
	create_vocabulary(trainingSet, vocabrary);
	for(auto &itr: vocabrary){
		cout << itr << ',';
	}
	/*
	//cout << "\n== After readFile() ==" << endl;
	for (const sentence &itr : trainingSet)
	{
		//cout << "Text: " << itr.text << " | ClassLabel: " << itr.classLabel << endl;
		for(auto &itr2: itr.text){
			cout << itr2 << '|';
		}
		cout << itr.classLabel << endl;
	}
	*/
	return 0;
}
/* http://vivi.dyndns.org/tech/cpp/string.html#swap */
vector<string> split(const string &str, char sep)
{
    std::vector<std::string> v;
    auto first = str.begin();
    while( first != str.end() ) {
        auto last = first;
        while( last != str.end() && *last != sep )
            ++last;
        v.push_back(std::string(first, last));
        if( last != str.end() )
            ++last;
        first = last;
    }
    return v;
}


void readFile(char *in_file, vector<sentence> &v ) //vector<string> &vocabulary, vector<vector<string>> &feature
{
	ifstream ifs(in_file);
	if (ifs.fail()) {
	cerr << "Failed to open file for input.\n" << endl;
	exit(1);
    }

	int index = 0, counter = 0;
	string line;

	// These two while loops will tokenize the entire text file and put it into a vector
	while (getline(ifs, line))
	{
		v.push_back(sentence()); // Create a new spot for a sentence

		stringstream ss(line);
		while (getline(ss, line, '\t'))
		{
			if ((counter % 2) == 0) // for text
			{
				//cout << "Text: " << line << endl;
				v[index].text = split(line, ' ');
				proper_word(v[index].text);
			}
			else if ((counter % 2) == 1) // for classLabel
			{
				int numClassLabel = stoi(line);
				//cout << "ClassLabel: " << numClassLabel << endl;
				v[index].classLabel = numClassLabel;
			}

			counter += 1;
		}

		index += 1;
	}

	ifs.close();


}
/*
	delete punctuation and convert into lower case
******************************************************/
void proper_word(vector<string> &text)
{
	int size_i = text.size();
	for(int i = 0; i < size_i; ++i){
		//string tmp = text[i];
		int size_j = text[i].size();
		for(int j = 0; j < size_j; ++j){
			/* if punct (I used ispunct() but there was weird behavior)
				I use !isalnum because of the French word(π⌐)
			*/
			if(!isalnum(text[i][j])){
				/* had to declere the number of erase elements */
				text[i].erase(j--,1);
				size_j = text[i].size();
			}
		}
		/* http://www.toshioblog.com/archives/23295983.html#title2 */
		transform(text[i].begin(), text[i].end(), text[i].begin(), ::tolower);
		/*
		size_j = text[i].size();
		for(int j = 0; j < size_j; ++j){
			if(isupper(text[i][j])){
				std::tolower(text[i][j]);
			}
		}*/
		/*if empty, delete*/
		if(text[i].empty()){
			text.erase(text.begin()+i);
			i--;
			size_i=text.size();

		}
		//text[i] = tmp;
		//cout << text[i];
	}
	//cout << endl;
}
/*
	push all text into vocabulary and sort it ( sort(vocabulary.begin(), vocabulary.end()); ). then vocabulary.erase(std::unique(vocabulary.begin(), vocabulary.end()), vocabulary.end());
***********************************************************************************/
void create_vocabulary(vector<sentence> &trainingSet, vector<string> &vocabulary)
{
	for(auto &itr: trainingSet){
		for(int i = 0; i < itr.text.size(); ++i){
			vocabulary.push_back(itr.text[i]);
		}
	}
	sort(vocabulary.begin(), vocabulary.end());
	vocabulary.erase(unique(vocabulary.begin(), vocabulary.end()), vocabulary.end());
	vocabulary.push_back("classlabel");
}
/*
	convert vector of sentence into feature vector
************************************/
void convert_process(vector<sentence> &sentenceSet, vector<string> &vocabulary, vector<vector<string>> &converted_sentenceSet)
{

}

void classification();