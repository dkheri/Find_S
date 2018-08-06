#include <iostream>
#include <vector>
#include <fstream>

using  namespace std;

void print(vector<string> data)
{
    for(const string& attr:data)
    {
        cout<<attr<<endl;
    }
}


vector<string> extract_attributes(string line)
{
    string delimiter=" ";
    vector<string> training_data;
    for(int i=0;i<7;i++)
    {
        string attr=line.substr(0,line.find(delimiter));
        training_data.push_back(attr);
        line=line.substr(line.find(delimiter)+1);
    }
    return training_data;
}

vector<vector<string>> extract_training_data(const string& in_file)
{
    string line;
    ifstream in;
    in.open(in_file);
    vector<vector<string>> training_set;
    while(getline(in,line))
    {
        training_set.push_back(extract_attributes(line));
    }
    return training_set;
}


vector<string>& re_evaluate_hypothesis(vector<string>& hypothesis,vector<string>& data)
{
        for(int i=0;i<hypothesis.size();i++) {
            if (hypothesis[i] != "?") {
                if (hypothesis[i] != data[i]) {
                    hypothesis[i] = "?";
                }
            }
        }

       return hypothesis;
}

vector<string> Find_S(vector<vector<string>>& training_set)
{
    vector<string> hypothesis;
    for(int i=0;i<training_set.size();i++)
    {
        if(training_set[i][training_set[i].size()-1]=="Yes"){
            if (i == 0) hypothesis = training_set[i];
            else { hypothesis = re_evaluate_hypothesis(hypothesis, training_set[i]); }
        }
    }

    return hypothesis;
}



int main() {

    vector<vector<string>> training_set=extract_training_data("in.txt");
    vector<string> data=Find_S(training_set);
    print(data);
    return 0;
}