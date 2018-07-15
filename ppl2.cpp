#include <bits/stdc++.h>
using namespace std;

vector<pair<string,string> > dataType;
map<string,string> typDef;
vector<string> internalNameEquivalence[9999];
vector<string> structNames[99999];
vector<string> funcInput[9999];
vector<string> funcOutput[9999];
int totInternalEquivalence;
int totStructs;
int totFuncs;
bool streq[9999][9999];
bool funceq[9999][9999];

bool isArray(string s)
{
	for(int i = 0; i < s.length(); i++)
	{
		if(s[i] == '[')
		{
			return true;
		}
	}
	return false;
}
	

bool isPointer(string s)
{
	for(int i = 0; i < s.length(); i++)
	{
		if(s[i] == '*')
		{
			return true;
		}
	}
	return false;	
}


bool checkFunctionEquivalence(int x, int y)
{
	if((funcInput[x].size() != funcInput[y].size()) || (funcOutput[x].size() != funcOutput[y].size()))
	{
		return false;
	}
	else
	{
		for(int i = 1; i < funcInput[x].size(); i++)
		{
			if(funcInput[x][i][funcInput[x][i].size() - 1] != '*' && funcInput[y][i][funcInput[y][i].size() - 1] != '*')
			{
				if(funcInput[x][i] != funcInput[y][i])return false;
			}
			else
			{
				if((funcInput[x][i] == "int*") || (funcInput[x][i] == "string*") || (funcInput[x][i] == "float*"))
				{
					if(funcInput[x][i] != funcInput[y][i])
					{
						return false;
					}
				}
				else
				{
					int t1, t2;
					string x11 = funcInput[x][i].substr(0,funcInput[x][i].size() - 1);
					string y11 = funcInput[y][i].substr(0,funcInput[y][i].size() - 1);
					for(int i = 0; i < totStructs; i++)
					{
						if(structNames[i][0] == x11)
						{
							t1 = i;
						}
					}
					for(int i = 0; i < totStructs; i++)
					{
						if(structNames[i][0] == y11)
						{
							t2 = i;
						}
					}
					if(streq[t1][t2] == false)return false;
				}
			}
		}
	}
	if((funcOutput[x].size() != funcOutput[y].size()) || (funcOutput[x].size() != funcOutput[y].size()))
	{
		return false;
	}
	else
	{
		for(int i = 1; i < funcOutput[x].size(); i++)
		{
			if(funcOutput[x][i][funcOutput[x][i].size() - 1] != '*' && funcOutput[y][i][funcOutput[y][i].size() - 1] != '*')
			{
				if(funcOutput[x][i] != funcOutput[y][i])return false;
			}
			else
			{
				if((funcOutput[x][i] == "int*") || (funcOutput[x][i] == "string*") || (funcOutput[x][i] == "float*"))
				{
					if(funcOutput[x][i] != funcOutput[y][i])
					{
						return false;
					}
				}
				else
				{
					int t1, t2;
					string x11 = funcOutput[x][i].substr(0,funcOutput[x][i].size() - 1);
					string y11 = funcOutput[y][i].substr(0,funcOutput[y][i].size() - 1);
					for(int i = 0; i < totStructs; i++)
					{
						if(structNames[i][0] == x11)
						{
							t1 = i;
						}
					}
					for(int i = 0; i < totStructs; i++)
					{
						if(structNames[i][0] == y11)
						{
							t2 = i;
						}
					}
					if(streq[t1][t2] == false)return false;
				}
			}
		}
	}
	return true;
}

bool checkStructuralEquivalence(int x, int y)
{
	if(structNames[x].size() != structNames[y].size())
	{
		return false;
	}
	for(int i = 1; i < structNames[x].size(); i++)
	{
		if((structNames[x][i][structNames[x][i].size()-1] == '*') && (structNames[y][i][structNames[y][i].size()-1] == '*'))
		{
			if((structNames[x][i] == "int*") || (structNames[x][i] == "string*") || (structNames[x][i] == "float*"))
			{
				if(structNames[x][i] != structNames[y][i])
				{
					return false;
				}
			}
			int x1, y1;
			for(int j = 0; j < totStructs; j++)
			{
				if(structNames[j][0] == structNames[x][i].substr(0,structNames[x][i].size()-1))
				{
					x1 = j;
				}
				if(structNames[j][0] == structNames[y][i].substr(0,structNames[y][i].size()-1))
				{
					y1 = j;
				}
			}
			if(streq[x1][y1] == false)return false;
		}
		else if(structNames[x][i] != structNames[y][i])
		{
			return false;
		}
	}
	return true;
}

string checkNameEquivalence(string x, string y)
{
	string x1, y1;
	for(int i = 0; i < dataType.size(); i++)
	{
		if(x == dataType[i].second)
		{
			x1 = dataType[i].first;
			if(isArray(dataType[i].first))
			{
				return "False as they are incompatible types";
			}
			if(isPointer(dataType[i].first))
			{
				return "False as they are incompatible types";
			}
			if(dataType[i].first == "function")
			{
				return "False as they are incompatible types";
			}
		}
		else if(y == dataType[i].second)
		{
			y1 = dataType[i].first;
			if(isArray(dataType[i].first))
			{
				return "False as they are incompatible types";
			}
			if(isPointer(dataType[i].first))
			{
				return "False as they are incompatible types";
			}
			if(dataType[i].first == "function")
			{
				return "False as they are incompatible types";
			}
		}
	}
	if(x1 == y1)return "True as they follow Name Equivalence";
	return "False as basic types follow Name Equivalence";
}

string checkInternalNameEquivalence(string x, string y)
{
	bool fir = false, sec = false;
	for(int i = 0; i < totInternalEquivalence; i++)
	{
		fir = false;
		sec = false;
		for(int j = 0; j < internalNameEquivalence[i].size(); j++)
		{
			if(internalNameEquivalence[i][j] == x)
			{
				fir = true;
			}
			if(internalNameEquivalence[i][j] == y)
			{
				sec = true;
			}
		}
		if(fir && sec)
		{
			return "Yes";
		}
	}
	return "No";
}

int main()
{
	ifstream infile("ppltest.txt");
	string line = "";
	int flg = 0;
    while (getline(infile, line)){
        stringstream strstr(line);
        string word = "";
        while (getline(strstr,word, ' '))
        {
        	string func;
        	if(word == "function")
        	{
        		getline(strstr,word,'[');
        		func = word;
        		dataType.push_back(make_pair("function",word));
        		funcInput[totFuncs].push_back(word);
        		funcOutput[totFuncs].push_back(word);
        		getline(strstr,word,']');
        		int prev = 0;
        		for(int i = 0; i < word.length(); i++)
        		{
        			if(word[i] == ' ')
        			{
        				string x11= word.substr(prev,i-prev);
        				while(typDef.find(x11) != typDef.end())
        				{
        					x11 = typDef[x11];
        				}
        				if(x11[x11.length() - 1] == '*')
        				{
        					x11 = x11.substr(0,x11.length() - 1);
        					while(typDef.find(x11) != typDef.end())
        					{
        						x11 = typDef[x11];
        					}
        					x11 += '*';		
        				}
        				funcInput[totFuncs].push_back(x11);
        				for(int j = i+1; j < word.length(); j++)
        				{
        					if(word[j] == ' ')
        					{
        						i = j;
        						break;
        					}
        				}
        				prev = i+1;
        			}
        		}	
        		getline(strstr,word,'[');
        		getline(strstr,word,']');
        		prev = 0;
        		for(int i = 0; i < word.length(); i++)
        		{
        			if(word[i] == ' ')
        			{
        				funcOutput[totFuncs].push_back(word.substr(prev,i-prev));
        				for(int j = i+1; j < word.length(); j++)
        				{
        					if(word[j] == ' ')
        					{
        						i = j;
        						break;
        					}
        				}
        				prev = i+1;
        			}
        		}
        		totFuncs++;
        		while (getline(infile, line))
        		{
        			if(line == "}")break;
        		}
        	}
        	else if(word == "struct")
        	{
        		while (getline(strstr,word, ' '))
        		{
        			structNames[totStructs].push_back(word);
        		}
        		while (getline(infile, line))
        		{
        			if(line == "{")continue;
        			if(line == "}")
        			{
        				break;
        			}
        			else
        			{
        				int flg = 0;
        				string x1;
        				stringstream strstr2(line);
        				while (getline(strstr2,word, ' '))
        				{
        					x1= word;
        					while(typDef.find(x1) != typDef.end())
        					{
        						x1 = typDef[x1];
        					}
        					while (getline(strstr2,word, ','))
        					{
        						structNames[totStructs].push_back(x1);
        					}	
        				}
        			}
        		}
        		totStructs++;
        	}
        	else if(word == "typedef")
        	{
        		string x1, y1;
        		int flg=0;
        		while(getline(strstr,word, ' '))
        		{
        			if(flg == 0)
        			{
        				x1 = word;
        				flg = 1;
        			}
        			else y1 = word;
        		}
        		typDef[y1] = x1;
        	}
        	else
        	{
        		string typ = word;
        		while(getline(strstr,word, ','))
        		{
        			dataType.push_back(make_pair(typ,word));
        			internalNameEquivalence[totInternalEquivalence].push_back(word);
        		}
        		totInternalEquivalence++;
        	}
        } 
    }
    string x, y;
    for(int i = 0; i < totStructs; i++)for(int j = 0; j < totStructs; j++)streq[i][j] = true;
    int chng = 1;
    while(chng >= 1)
    {
    	chng = 0;
    	for(int i = 0; i < totStructs; i++)
    	{
    		for(int j = i+1; j < totStructs; j++)
    		{
    			streq[i][j] = checkStructuralEquivalence(i,j);
    			if(streq[i][j] != streq[j][i])
    			{
    				chng++;
    			}
    			streq[j][i] = streq[i][j];
    		}
    	}
    }
    for(int i = 0; i < totFuncs; i++)
    {
    	for(int j = 0; j < totFuncs; j++)
    	{
    		funceq[i][j] = true;
    	}
    }
    for(int i = 0; i < totFuncs; i++)
    {
    	for(int j = i+1; j < totFuncs; j++)
    	{
    		funceq[i][j] = checkFunctionEquivalence(i,j);
    		funceq[j][i] = funceq[i][j];
    	}
    }
    string loll1, loll2;
    while(true)
    {
    	cin >> x >> y;
        for(int i = 0; i < dataType.size(); i++)
        {
            if(dataType[i].second == x)
            {
                loll1 = dataType[i].first;
            }
        }
        for(int i = 0; i < dataType.size(); i++)
        {
            if(dataType[i].second == y)
            {
                loll2 = dataType[i].first;
            }
        }
        int isstr44 = -1, isstr55 = -1;
        for(int j = 0; j < totStructs; j++)
        {
            if(structNames[j][0] == loll1)
            {
                isstr44 = j;
            }
            if(structNames[j][0] == loll2)
            {
                isstr55 = j;
            }
        }
        if(isstr44 != -1)
        {
            if(isstr55 == -1)
            {
                cout << "False as they are incompatible types\n";
            }
            else
            {
                if(streq[isstr44][isstr55] == false)cout << "False as structs follow Structural Equivalence\n";
                else cout << "True as they follow Structural Equivalence\n";   
            }
            continue;
        }
        for(int i = 0; i < dataType.size(); i++)
        {
            if(dataType[i].second == x && isArray(dataType[i].first))
            {
                for(int j = 0; j < dataType.size(); j++)
                {
                    if(dataType[j].second == y)
                    {
                        if(isArray(dataType[j].first) && (dataType[i].first == dataType[j].first))
                        {
                            cout << "True as they follow Name Equivalence" << endl;
                        }
                        else
                        {
                            cout << "False as arrays follow Name Equivalence\n";
                        }
                        break;
                    }
                }
            }
            else if(dataType[i].second == x && dataType[i].first == "function")
            {
                for(int j = 0; j < dataType.size(); j++)
                {
                    if(dataType[j].second == y)
                    {
                        if(dataType[j].first == "function")
                        {
                            int t1, t2;
                            string x11 = dataType[i].second;
                            string y11 = dataType[j].second;
                            for(int i = 0; i < totFuncs; i++)
                            {
                                if(funcInput[i][0] == x11)
                                {
                                    t1 = i;
                                }
                            }   
                            for(int i = 0; i < totFuncs; i++)
                            {
                                if(funcInput[i][0] == y11)
                                {
                                    t2 = i;
                                }
                            }
                            if(funceq[t1][t2] == false)cout << "False as both functions are not Structural Equivalent\n";
                            else cout << "True as they follow Structural Equivalence\n";
                        }
                        else
                        {
                            cout << "False because they are incompatible types\n";
                        }
                    }
                }
            }
            else if(dataType[i].second == x && dataType[i].first[dataType[i].first.size() - 1] == '*')
            {
                for(int j = 0; j < dataType.size(); j++)
                {
                    if(dataType[j].second == y)
                    {
                        if(dataType[j].first[dataType[j].first.size() - 1] != '*')
                        {
                            cout << "False as pointers follow Structural Equivalence\n";
                        }
                        else 
                        {
                            string x11 = dataType[i].first;
                            x11 = x11.substr(0,x11.length() - 1);
                            while(typDef.find(x11) != typDef.end())
                            {
                                x11 = typDef[x11];
                            }
                            int isstr3 = -1;
                            for(int k = 0; k < totStructs; k++)
                            {           
                                if(structNames[k][0] == x11)
                                {
                                    isstr3 = k;
                                    break;
                                }
                            }
                            if(isstr3 != -1)
                            {
                                string y11 = dataType[j].first;
                                y11 = y11.substr(0,y11.length() - 1);
                                while(typDef.find(y11) != typDef.end())
                                {
                                    y11 = typDef[y11];
                                }
                                int isstr4 = -1;
                                for(int k = 0; k < totStructs; k++)
                                {           
                                    if(structNames[k][0] == y11)
                                    {
                                        isstr4 = k;
                                        break;
                                    }
                                }
                                if(isstr4 == -1)
                                {
                                    cout << "False as pointers follow Structural Equivalence\n";
                                }
                                else
                                {
                                    if(streq[isstr4][isstr3] == 0)
                                    {
                                        cout << "False as pointers follow Structural Equivalence\n";
                                    }
                                    else cout << "True as they follow Structural Equivalence\n";
                                }
                                break;
                            }
                            x11 += '*';
                            string y11 = dataType[j].first;
                            y11 = y11.substr(0,y11.length() - 1);
                            while(typDef.find(y11) != typDef.end())
                            {
                                y11 = typDef[y11];
                            }    
                            y11 += '*';
                            if(x11 == y11)  
                            cout << "True as they follow Structural Equivalence\n";
                            else cout << "False as pointers follow Structural Equivalence\n";
                            break;
                        }
                    }
                }
            }
            else if(dataType[i].second == x)
            {
                cout << checkNameEquivalence(x,y) << endl;        
            }    
        }    
    }
	return 0;
}