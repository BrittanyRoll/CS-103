#include "web.h"
#include <vector>

Web::Web() 
{ 

}

Web::~Web() 
{ 

}

 /*
     reads in and parse graph from a file.
     @filename: is the name of the file describing the webgraph.
     @return: true in success , and false in failure.
    */
bool Web::read_graph(const char *filename) 
{ 
    ifstream pgs(filename);
    if (pgs.fail()) {
        cout << "Failed to open!" << endl;
        pgs.close();
        return false;
    }
    
    int npgs; //num of pages
    int pages; //id
    string url, line;
    double page_rank;
    vector<Page> pglist;
    
    pgs >> npgs; //get num pages
    if(pgs.fail()) {
        cout << "Failed to get number" << endl;
        pgs.close();
        return false;
    }
    
    
    for (int i = 0; i < npgs; i++) {
        //page id
        pgs >> pages;
        //getline(pgs, line); //use to get white space after page rank
        //page url, make instance of page
        pgs >> url;
        //pagerank
        pgs >> page_rank;
        //pages it links to, need to use mix of get line and stringstream
        getline(pgs, line);
        getline(pgs, line);
        stringstream lnks(line);
        int nums;
        vector<int> link_dat;
        while (lnks >> nums) { //works
            //cout << "link num is " << nums << endl;
            link_dat.push_back(nums);
        }
        
        Page* dat = new Page;
        dat->set_id(pages);
        dat->set_url(url);
        dat->set_prank(page_rank);
        dat->set_links(link_dat);
        pglist.push_back(*dat); //put page into list of pages
        if (i == (npgs-1)) {
            pagelist = pglist;
        }
        //empty list for next page
        delete dat; //do this here?
        
    }
    pgs.close(); 
    return true;
}

 /*
     writes out webgraph to a file.
     @filename: is the name of the file to write to.
     @return: true in success , and false in failure
    */
bool Web::write_graph(const char *filename)
{ 
    ofstream myfile(filename);
    if(myfile.fail()) {
        cout << "Failed!" << endl; //fail to open file
        myfile.close();
        return false;
    }
    
    int sizes = pagelist.size();
    myfile << sizes << "\n";
    cout << sizes << "\n";
    
    for (int i = 0; i < sizes; i++) {
        myfile << pagelist.at(i).access_id() << "\n";
        myfile << "\t" << pagelist.at(i).access_url() << "\n";
        myfile << "\t" << pagelist.at(i).access_prank() << "\n";
        

        int counter = 0;
        
        myfile << "\t";
        cout << "\t";
        while (counter < pagelist.at(i).access_links().size()) {
            if (counter == pagelist.at(i).access_links().size() - 1) {
                myfile << pagelist.at(i).access_links().at(counter) << "\n";
                cout << pagelist.at(i).access_links().at(counter) << "\n";
            } else {
                myfile << pagelist.at(i).access_links().at(counter) << " ";
                cout << pagelist.at(i).access_links().at(counter) << " ";
            }
            
            counter++;
        }  
    }
    myfile.close();
    return true;
}

 /*
     calculates the rank of the pages
     @S: is the number of simulation iteration.
     @N: is the number of surfer
    */



void Web::calculate_rank(int S,int N)
{
    
    int old_walkers[pagelist.size()]; //declare array w/#walkers on each page 
    int new_walkers[pagelist.size()];
    
    for(int i = 0; i < pagelist.size(); i++) {
             old_walkers[i] = N/pagelist.size();
             new_walkers[i] = 0;
    }
    if(N%pagelist.size() != 0) { //put extra walkers on each page
        int counter = 0;
        while(counter < N%pagelist.size()) {
            old_walkers[counter] += 1;
            counter++;
        }
    }
    
    for(int k = 0; k < S; k++) { //run through simulations
         for(int i = 0; i < pagelist.size(); i++) { //go through each page
           if(pagelist.at(i).access_links().size() > 0) {
             int count = 0;
             while(count < old_walkers[i]) {
                int num_links = pagelist.at(i).access_links().size(); //access number of links from page
                int lnk_num = rand()%num_links;
                int rand_lnk = pagelist.at(i).access_links().at(lnk_num); //page that is linked to
                new_walkers[rand_lnk]++; //walker goes to next page
                count++;
             }
           } else {
               new_walkers[i] += old_walkers[i];
           }
         }
         //switch old and new walkers for next simulation
         for(int i = 0; i < pagelist.size(); i++) {
             old_walkers[i] = new_walkers[i];
             new_walkers[i] = 0;
         }     
    }
    //set pagerank
    for(int i = 0; i < pagelist.size(); i++) {
        pagelist.at(i).set_prank((double)old_walkers[i]/N);
    }
  
      
} 

//error with simple_graph.txt
    
