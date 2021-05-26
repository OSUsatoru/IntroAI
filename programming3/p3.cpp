// Group members: Satoru Yamamoto,

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
void convert_process(char *out_file, vector<sentence> &sentenceSet, vector<string> &vocabulary, vector<vector<string>> &converted_sentenceSet);
void classification_training(vector<vector<string>> &converted_sentenceSet, vector<pair<float,float>> &training_prob, vector<pair<float,float>> &training_prob2);
float classification_testing(vector<vector<string>> &converted_sentenceSet,  vector<pair<float,float>> &training_prob, vector<pair<float,float>> &training_prob2);
/*
	argv[1] is the
***********************************/
int main(int argc, char *argv[])
{
	vector<sentence> testSet, trainingSet;
	vector<string> vocabrary;
	vector<vector<string>> converted_testSet, converted_trainingSet;

	char testText[] = "testSet.txt", trainingText[] = "trainingSet.txt";
	char test_out[] = "preprocessed_test.txt", training_out[]="preprocessed_train.txt";

	/* Get the data into testSet and trainingSet */
	readFile(testText, testSet);
	readFile(trainingText, trainingSet);
	/* Create feature vector */
	create_vocabulary(trainingSet, vocabrary);
	/*
	for(auto &itr: vocabrary){
		cout << itr << ',';
	}
	*/
	convert_process(test_out,testSet,vocabrary,converted_testSet);
	convert_process(training_out,trainingSet,vocabrary,converted_trainingSet);

	vector<pair<float,float>> first_training(vocabrary.size(), pair<float,float>(0.0,0.0));
	vector<pair<float,float>> first_training2(vocabrary.size(), pair<float,float>(0.0,0.0));
	//cout << vocabrary.size();
	classification_training(converted_trainingSet, first_training,first_training2);
	float accurate_first, accurate_second;
	accurate_first = classification_testing(converted_trainingSet, first_training, first_training2);
	accurate_second = classification_testing(converted_testSet, first_training, first_training2);


		/* print  */
	ofstream ofs("result.txt");
	if (!ofs) {
        cerr << "Could not open output file.\n" << endl;
        exit(1);
    }
	ofs << "acuarate trainingSet: " << accurate_first << '\n';
	ofs << "acuarate testSet: " << accurate_second;


	ofs.close();
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
void convert_process(char *out_file, vector<sentence> &sentenceSet, vector<string> &vocabulary, vector<vector<string>> &converted_sentenceSet)
{

	// check each sentence
	for(int i = 0; i < sentenceSet.size(); ++i){
		//edit this and push_back into converted_sentenceSet
		vector<string> tmp(vocabulary.size(),"0");
		if(sentenceSet[i].classLabel==1){
			tmp[vocabulary.size()-1] = "1";
		}
		//check each word
		for(int j = 0; j < sentenceSet[i].text.size(); ++j){
			//if the word is in the vocabulary
			for(int k = 0; k < vocabulary.size()-1; ++k){
				//if find, tmp[k] = "1"
				if(vocabulary[k].compare(sentenceSet[i].text[j]) == 0){
					tmp[k] = "1";
				}
			}
		}
		converted_sentenceSet.push_back(tmp);
	}


	/* print  */
	ofstream ofs(out_file);
	if (!ofs) {
        cerr << "Could not open output file.\n" << endl;
        exit(1);
    }
	/* print the vocabulary */
	for(int i = 0; i < vocabulary.size(); ++i){
		ofs << vocabulary[i];
		if(i!=vocabulary.size()-1){
			ofs << ',';
		}else{
			ofs << '\n';
		}
	}
	for(int i = 0; i < converted_sentenceSet.size(); ++i){
		for(int j = 0; j < converted_sentenceSet[i].size(); ++j){
			ofs << converted_sentenceSet[i][j];
			if(j!=converted_sentenceSet[i].size()-1){
				ofs << ',';
			}else if(i!=converted_sentenceSet.size()-1){
				ofs << '\n';
			}
		}
	}


	ofs.close();
}
/***
 1. need to create (pair of floating numbers) for each words (training)
- (x=1 given CL=1) and (x=0 given CL = 0)
- for CL, pair value is P(CL=1) and P(CL=0)
- vector<pair<float,float>> trained_text(vocabulary.size());
- for each vocabulary, ((#of x=1 and CL=1)+1) / ((# of CL=1)+2)
- and ((#of x=0 and CL=0)+1) / ((# of CL=0)+2)


 ******************************************/
void classification_training(vector<vector<string>> &converted_sentenceSet, vector<pair<float,float>> &training_prob, vector<pair<float,float>> &training_prob2)
{
	// converted_sentenceSet[0].size() is number of words
	//  converted_sentenceSet.size() is number of sentences
	float good_CL = 0., bad_CL = 0.;
	for(int i = 0; i < converted_sentenceSet.size(); ++i){
		if(converted_sentenceSet[i][converted_sentenceSet[i].size()-1] == "1"){
			++good_CL;
		}else{
			++bad_CL;
		}
	}
	training_prob[converted_sentenceSet[0].size()-1].first = good_CL/converted_sentenceSet.size();
	training_prob[converted_sentenceSet[0].size()-1].second = bad_CL/converted_sentenceSet.size();
	training_prob2[converted_sentenceSet[0].size()-1].first = good_CL/converted_sentenceSet.size();
	training_prob2[converted_sentenceSet[0].size()-1].second = bad_CL/converted_sentenceSet.size();
	// counting is fine-----
	// count vocabulary = 1 and cl = 1 or vocabulary = 0 and cl = 0.
	// no need to check converted_sentenceSet[][converted_sentenceSet[].size()-1]

	for(int i = 0; i < converted_sentenceSet[0].size()-1; ++i){
		float good_pair = 0., bad_pair = 0.;
		float good_bad = 0., bad_good = 0.;
		// want to see converted_sentenceSet[j][i]
		for(int j = 0; j < converted_sentenceSet.size(); ++j){
			/*case of the CL*/

			if(converted_sentenceSet[j][i].compare("1")==0 and converted_sentenceSet[j][(converted_sentenceSet[0].size()-1)].compare("1")==0){
				++good_pair;
			}else if(converted_sentenceSet[j][i].compare("0")==0 and converted_sentenceSet[j][(converted_sentenceSet[0].size()-1)].compare("0") == 0){
				++bad_pair;
			}else if(converted_sentenceSet[j][i].compare("1")==0 and converted_sentenceSet[j][(converted_sentenceSet[0].size()-1)].compare("0") == 0){
				++good_bad;
			}else if(converted_sentenceSet[j][i].compare("0")==0 and converted_sentenceSet[j][(converted_sentenceSet[0].size()-1)].compare("1") == 0){
				++bad_good;
			}

		}
		//cout << good_pair << ' ' << bad_pair <<endl;
		training_prob[i].first = (float)(good_pair+1)/(float)(good_CL+2);
		training_prob[i].second = (float)(bad_pair+1)/(float)(bad_CL+2);

		training_prob2[i].first = (float)(good_bad+1)/(float)(good_CL+2);
		training_prob2[i].second = (float)(bad_good+1)/(float)(bad_CL+2);
	}
	//cout <<converted_sentenceSet[0].size();
	/*
	cout << good_CL << ' ' << bad_CL << endl;
	for(int i = 0; i < training_prob.size(); ++i){
		cout << (1-training_prob[i].first)+training_prob2[i].first << ' ' << (1-training_prob[i].second)+training_prob2[i].second << endl;
	}*/

}
/*
	2. calculate max prob (testing)
	- for v=1, log( P(CL=1) + sum_words( log(P(X=1,CL=1) + log( 1 - P(X=1,CL=1) )
	- for v=0, log( P(CL=0) + sum_words( log( 1 - P(X=1,CL=0) ) + log( P(X=1,CL=0) )
********************************/

float classification_testing(vector<vector<string>> &converted_sentenceSet,  vector<pair<float,float>> &training_prob, vector<pair<float,float>> &training_prob2)
{
	// chech each words to predict -> count it
	int correct = 0;
	float predict_good = 0., predict_bad = 0.;
	//loop all of statement (need to see each CL)
	for(int i=0; i < converted_sentenceSet.size(); ++i){

		// loop all vocab
		for(int j=0; j < converted_sentenceSet[0].size()-1; ++j){

			if(converted_sentenceSet[i][j].compare("1") == 0){
				predict_good += log10(training_prob[j].first);
				predict_bad += log10(training_prob[j].second);
			}else{
				predict_good += log10(1-training_prob[j].first);
				predict_bad += log10(1-training_prob[j].second);
			}
			/*
			predict_good += log10(training_prob[j].first);
			predict_bad += log10(training_prob[j].second);
			predict_good += log10(1-training_prob[j].first);
			predict_bad += log10(1-training_prob[j].second);
			*/
		}
		predict_good+= log10(training_prob[converted_sentenceSet[0].size()-1].first);
		predict_bad+= log10(training_prob[converted_sentenceSet[0].size()-1].second);
		//cout << predict_good << ' ' << predict_bad;
		if(predict_good > predict_bad){
			if(converted_sentenceSet[i][converted_sentenceSet[0].size()-1] == "1"){
				correct++;
			}
		}else{
			if(converted_sentenceSet[i][converted_sentenceSet[0].size()-1] == "0"){
				correct++;
			}
		}
	}
	//cout << correct << ' ' << converted_sentenceSet.size()<<endl;
	float result = (float)correct/(float)converted_sentenceSet.size();
	//cout << result ;
	return result;
}