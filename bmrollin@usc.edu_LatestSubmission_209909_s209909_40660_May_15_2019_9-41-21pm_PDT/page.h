#ifndef PAGE_H
#define PAGE_H
#include <string>
using std::string;
#include<vector>
using std::vector;
class Page { 
public:
  Page(); //need parameter?
  ~Page();
  //setters and getters
  //getters
  int access_id();
  string access_url();
  vector<int>& access_links(); //is this right?
  double access_prank();
  vector<Page> access_pages();
  //setters
  void set_id(int n);
  void set_url(string s);
  void set_links(vector<int> link);
  void set_prank(double new_prank);
  void set_pages(vector<Page>);
  //vector<Page> pagelist;
    
private:
  //Data members: id, url, pagerank, links , .. etc
  int id;
  string url;
  vector<int> links;
  double pagerank;
};  
#endif