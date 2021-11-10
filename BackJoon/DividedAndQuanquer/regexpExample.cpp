
#include <iostream>
#include <regex>
#include <map>
#include <vector>

using namespace std;

int main() 
{

    std::string html = R"(
    <html lang="ko" xml:lang="ko" xmlns="http://www.w3.org/1999/xhtml">
    <head>
        <meta charset="utf-8">
        <meta property="og:url" content="https://a.com"/>
    </head>  
    <body>
        Blind Lorem Blind ipsum dolor Blind test sit amet, consectetur adipiscing elit. 
        <a href="https://b.com"> Link to b </a>
    </body>
    </html>)";

    //std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");
    
   // regex url(R"(<meta [\w]*content="([\w]*)\"[\w]*>)"); 
    regex url(R"(<meta .* content="(.*)\"\/>)");   
    std::smatch match;
    regex_search(html, match, url);
    cout << "Match : " << match[1].str() << '\n';

    
    vector<string> links;
    regex link(R"(<a href="(.*)\">)");
    auto start = std::sregex_iterator(html.begin(), html.end(), link);
    auto end = std::sregex_iterator();
    for (std::sregex_iterator i = start; i != end; ++i) 
    {
        std::smatch match = *i;                                                 
        links.push_back(match[1].str());
    }  

    for(string & iter : links)
        cout << iter << endl;
    
    string word = "Blind";
    regex w(word);
    auto start2 = std::sregex_iterator(html.begin(), html.end(), w);
    auto end2 = std::sregex_iterator();
    int cnt = distance(start2, end2);
    cout << cnt << endl;
}


map<string, int> urlIdx;
vector<int> points;
vector<vector<int>> outLinks;

void parsePage(const string & page, const string & word)
{
    int basePoint=0;
    string sUrl;
    vector<string> links;
    
    regex url(R"(<meta .* content="(.*)\"\/>)");   
    std::smatch match;
    regex_search(page, match, url);
    sUrl = match[1].str();

    
    regex link(R"(<a href="(.*)\">)");
    auto start = std::sregex_iterator(page.begin(), page.end(), link);
    auto end = std::sregex_iterator();
    for (std::sregex_iterator i = start; i != end; ++i) 
    {
        std::smatch match = *i;                                                 
        links.push_back(match[1].str());
    }  
    
    string word = "Blind";
    regex w(word);
    auto start2 = std::sregex_iterator(html.begin(), html.end(), w);
    auto end2 = std::sregex_iterator();
    int cnt = distance(start2, end2);
    cout << cnt << endl;
}