//
// Created by Aris  Emery on 4/17/17.
//

#include "PortScanAnalyzer.h"
void PortScanAnalyzer::dataSummation(ifstream &inputFile) {
    string currentIP;
    string port;
    string lineGarbage;
    int counter = 0;
    int iterations = 0;
    int intPort;
    int index;
    char delim = '\n';
    vector<int> *newEntry;
    while (inputFile.is_open() && !inputFile.eof() && counter < 500) {
        getline(inputFile, lineGarbage, ',');
        getline(inputFile, currentIP, ',');
        getline(inputFile, port, ',');
        getline(inputFile, lineGarbage, delim);
        intPort = convertStringToInt(port);
        if (data.containsKey(currentIP) != true) {
            newEntry = new vector<int>;
            data.add(currentIP, *newEntry);
            int what = data.getCount();
        }
        bool found = false;
        for (int i = 0; i < data.getValueByKey(currentIP).size() && found == false; i++) {
            if (data.getValueByKey(currentIP)[i] == intPort) {
                found = true;
            }
        }
        if (!found) {
            index = data.returnIndex(currentIP);
            data.keyValuePairs[index]->m_value.push_back(intPort);
        }


        counter++;
    }

}
ResultSet PortScanAnalyzer::attackDetection(){
    ///Attack detection phase
    string currentIP;
    int likelyThreshold=myConfiguration.getIntValue("Likely Attack Port Count");
    int possibleThreshold=myConfiguration.getIntValue("Possible Attack Port Count");
    vector<string> *newEntry1;
    newEntry1= new vector<string>;
    ResultSet POSresults;
    POSresults.results.add("Likely attackers", *newEntry1);
    newEntry1= new vector<string>;
    POSresults.results.add("Possible attackers", *newEntry1);
    for (int i=0;i<data.getCount();i++){
        //*newEntry=data.getByIndex(i).m_value;
        currentIP=data.getByIndex(i).m_key;
        int saf=data.getByIndex(i).m_value.size();
        if(data.getByIndex(i).m_value.size()>=likelyThreshold){
            POSresults.results.keyValuePairs[0]->m_value.push_back(currentIP);
        }
        else if(data.getByIndex(i).m_value.size()>=possibleThreshold){
            POSresults.results.keyValuePairs[1]->m_value.push_back(currentIP);
        }
    }
    return POSresults;

}