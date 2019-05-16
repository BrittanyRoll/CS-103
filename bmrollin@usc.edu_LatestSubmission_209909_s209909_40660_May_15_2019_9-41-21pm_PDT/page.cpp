#include "page.h"

Page::Page() 
{

}

Page::~Page(){
    
}

//getters

int Page::access_id(){
    return id;
}

string Page::access_url() {
    return url;
}

vector<int>& Page::access_links() { //is this right?
    return links;
}

double Page::access_prank() {
    return pagerank;
}

//setters
void Page::set_id(int n) {
    id = n;
}

void Page::set_url(string s) {
    url = s; //can you do this with strings
}

void Page::set_links(vector<int> link) { //what else?
    links = link;
}

void Page::set_prank(double new_prank) {
    pagerank = new_prank;
}

/*
vector<Page> Page::access_pages() {
    return pagelist;
}
 
void Page::set_pages(vector<Page> p) {
    pagelist = p;
}
*/