#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

string make_plural(size_t ctr, const string &word, const string ending)
{
    return (ctr > 1 ? word + ending : word);
}

class QueryResult
{
    friend ostream &print(ostream &, const QueryResult &);

public:
    using line_no = std::vector<string>::size_type;
    QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f) : sought(s), lines(p), file(f) {}

private:
    string sought;
    shared_ptr<set<line_no>> lines;
    shared_ptr<vector<string>> file;
};

class QueryResult;
class TextQuery
{
public:
    using line_no = std::vector<string>::size_type;
    TextQuery(ifstream &);
    QueryResult query(const string &) const;
    void runQueries(ifstream &infile)
    {
        TextQuery tq(infile);
        string s;
        while (true)
        {
            cout << "enter word to look for, or q to quit: " << endl;
            if (!(cin >> s) || s == "q")
                break;
            print(cout, query(s));
        }
    }

private:
    shared_ptr<vector<string>> file;
    map<string, shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream &is) : file(new vector<string>)
{
    string text;
    while (getline(is, text))
    {
        file->emplace_back(text);
        int n = file->size() - 1;
        istringstream line(text);
        string word;
        while (line >> word)
        {
            if (!wm[word])
                wm[word].reset(new set<line_no>);
            wm[word]->insert(n);
        }
    }
}

QueryResult TextQuery::query(const string &sought) const
{
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

ostream &print(ostream &os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << make_plural(qr.lines->size(), " time", "s") << endl;
    for (auto num : *qr.lines)
        os << "\t(line " << num + 1 << ")" << *(qr.file->begin() + num) << endl;
    return os;
}
int main()
{
    SetConsoleOutputCP(65001);
    ifstream infile("D:/TXT/words.TXT");
    TextQuery tq(infile);
    tq.runQueries(infile);
    system("pause");
    return 0;
}
