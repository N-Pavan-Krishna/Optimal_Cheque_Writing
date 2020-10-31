//
//  Pay.cpp
//  OptimalChequeWriting
//
//  Created by Pavan Krishna Nandimandalam on 2019-03-22.
//  Copyright © 2019 Pavan Krishna Nandimandalam. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    if(argc != 4)
    {
        cout << "Error: Incorrect number of arguments!!!" << endl;
        return -1;
    }
    
    fstream input(argv[1]);
    ofstream output(argv[2]);
    fstream cost(argv[3]);
    
    if(!input)
    {
        cout << "Error: Cannot open input file!!!" << endl;
        return -1;
    }
    
    if(!cost)
    {
        cout << "Error: Cannot open cost file!!!" << endl;
        return -1;
    }
    
    if(!output)
    {
        cout << "Error: Cannot open output file (Permission issue?) !!!" << endl;
        return -1;
    }
    
    pair<int, int> costPair[10001];
    
    for(int i=0;i<10001;i++){
        cost >> costPair[i].first;
        cost >> costPair[i].second;
    }
    
    int dataSet;
    int n,a,b;
    
    input >> dataSet;
    
    for(int i=0;i<dataSet;i++){
        
        input >> n >> a >> b;
        
        vector<int> start;
        
        int total=n*a;
        
        //Reading the possible start values to write cheque
        for(int j=0;j<b+1;j++){
            if(a+j<=total && a+j<=10000)
                start.push_back(a+j);
        }
        
        /*Printing the start vector
        for(int j=0;j<start.size();j++){
            cout << start[j] << endl;
        }*/
        
        int optimalPay=INT_MAX;
        vector<int> finalCombination;
        //finalCombination.resize(n);
        vector<int> combination;
        //combination.resize(n);
        for(int j=0;j<start.size();j++){ // For every start cost we will find subsequent best cost that can be included in the writing cheque
            int bCopy;
            bCopy=b-j;
            //cout << j << ":" << "start-" << start[j] <<  endl;
            //cout << "b-start:" << bCopy << endl;
            int paid=0;
            int current=start[j];
            //optimalPay=100;
            int pay=0;
            combination.clear();
            for(int k=1;k<=n;k++){
                //cout << "K:" << k << endl;
                //cout << "paid:" << paid << endl;
                //cout << "total:" << total << endl;
                
                int high=0;
                int highA=0;
                int low=0;
                if(paid==total){
                    //cout << "OptimalPay break:" << optimalPay << endl;
                    combination.push_back(0);
                    continue;
                }
                if(k==1){ // first period must be start cost
                    paid=paid+start[j];
                    //cout << current << " ";
                    combination.push_back(current);
                    pay=pay+costPair[current].second;
                    continue;
                }
                
                if(k==n){ // last period must be total-paid(till last before)
                    current = total-paid;
                    //cout << current << " ";
                    combination.push_back(current);
                    paid=paid+current;
                    pay=pay+costPair[current].second;
                    continue;
                }
                
                low=a*k;
                
                high=a*k+bCopy;
                highA=paid+a;
                
                if(high>10001)
                    high=a*k;
                if(highA>high)
                    high=highA;

                // 12 12 31
                if(low<paid){
                    low = paid;
                }
                // end of 12 12 31 testcase
                
                //cout << "B:" << bCopy << endl;
                //cout << "low:" << low << endl;
                //cout << "high:" << high << endl;
                vector<int> choose;
                for(int x=low;x<=high;x++){
                    choose.push_back(x);
                }
                
                int pCost=INT_MAX;
                int index=0;
                for(int x=0;x<choose.size();x++){
                    current = choose[x]-paid;
                    //cout << x << ":" << "paid:" << paid << " chosen value:" << choose[x] << "->" << current << endl;
                
                    if(costPair[current].second<pCost){
                        pCost=costPair[current].second;
                        index=current;
                    }
                }
                paid=paid+index;
                //cout << "paid:" << paid << endl;
                pay=pay+costPair[index].second;
                if(index>a)
                    bCopy=bCopy-(index-a);
                else
                    bCopy=bCopy+(a-index);
                combination.push_back(index);
                //cout << index << " ";
                
                //b--;
                
            } // end of n loop
            //cout << j << ":" ;
            //cout  << endl ;
            //cout << "Pay:" << pay << endl;
            //cout << j << ":" << pay << endl;
            //cout << "optimalPay Before:" << optimalPay << endl;
            if(pay<optimalPay){
                //finalCombination.clear();
                optimalPay=pay;
                finalCombination=combination;
            }
            else
                combination.clear();
            
            //cout << "optimalPay:" << optimalPay << endl;
        }
        if(i<dataSet-1)
            output << optimalPay << endl;
        else
            output << optimalPay ;
        //cout << "optimalPay:" << optimalPay << endl;
        
        for(int j=0;j<finalCombination.size();j++){
            cout << finalCombination[j] << " ";
        }
        
        cout << endl;
        
    }
}

