#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

using  namespace std;

vector<vector<string>> attributes={{"Sunny","Rainy"}, {"Warm","Cold"}, {"Normal","High"},
                                   {"Strong","Weak"}, {"Warm","Cool"}, {"Same","Change"}};
int num_attributes=attributes.size();

void print(vector<string> data)
{
    for(const string& attr:data)
    {
        cout<<attr<<" ";
    }
    cout<<endl;
}

void print(vector<vector<string>> set)
{
      for(const auto& data:set){
        print(data);
      }
}


vector<string> generate_random_training_example(vector<string> target)
{
    vector<string> example;
    string verdict= "Yes";
    int random_number;
    for(int i=0;i<num_attributes;i++)
    {
        random_number=rand()%2;
        example.push_back(attributes[i][random_number]);
        if(target[i]!="?" && target[i]!=example[i])
        {
            verdict="No";
        }
    }
    example.push_back(verdict);
    return example;
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
            if (i == 0) {hypothesis = training_set[i]; hypothesis.resize(num_attributes);}
            else { hypothesis = re_evaluate_hypothesis(hypothesis, training_set[i]); }
        }
    }
    return hypothesis;
}

int experiment(vector<vector<string>>& training_set,vector<string>& target_concept)
{
     int training_examples=0;
     std::srand(time(nullptr));
     while(Find_S(training_set)!=target_concept)
     {
         training_set.push_back(generate_random_training_example(target_concept));
         training_examples++;
     }

    return training_examples;
}


int main() {

    vector<vector<string>> training_set=extract_training_data("in.txt");
//    vector<string> hypo=Find_S(training_set);
    vector<string> target_concept={"Sunny","Warm","?","?","?","?"};
    cout<<experiment(training_set,target_concept);
    return 0;
}