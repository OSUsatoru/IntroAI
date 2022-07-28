
## Instruction
The goal of sentiment analysis is to determine the writer's attitude toward the topic about which they are writing. It can be applied to text from reviews and survey responses (and perhaps even course evaluations!) to determine whether the writer feels positively or negatively about the subject. In this assignment, you will predict the sentiment sentences taken from Yelp reviews, using data. You will be using naive Bayes for this classification problem. Given an input sentence, you are to determine whether a sentence is positive or negative.

In the training phase, the naive Bayes classifier reads in the training data along with the training labels and learns the parameters used by the classifier
In the testing phase, the trained naive Bayes classifier classifies the data in the testSet.txt data file. Use the preprocessed data you generated above.
Output the accuracy of the naive Bayes classifier by comparing the predicted class label of each sentence in the test data to the actual class label. The accuracy is the number of correct predictions divided by the total number of predictions.

## Example of compile a code program to create an executable file
```sh
g++ --std=c++11 p3.cpp -o p3
```
## Example of run program commands
```sh
.\p3.exe  > check.txt
```
