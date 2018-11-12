#include<bits/stdc++.h>
void populateFile(int count,std::string const& file)
{
    std::ofstream myfile(file);
    if (!myfile )
    {
       // Deal with error.
       return;
    }

    for(int index=0; index<count; index++)
    {
        int first= (rand()%99);
        myfile << first<<" ";
        //int second= (rand()%100)+1;
        myfile << first+1<<" ";
        int random_integer = (rand()%1000);
        myfile << random_integer << "\n";
    }
}

// void readFileAndBuildBST(std::string const& file,
//                          BinarySearchTree& b)
// {
//     std::ifstream myfile(file);
//     if (!myfile )
//     {
//        // Deal with error.
//        return;
//     }

//     int number;
//     while ( myfile >> number )
//     {
//        b.insert(number);
//     }
// }

void driver()
{
   // Seed the random number generator.
   srand( time( NULL ) );

   // Populate the file
   std::string file("output.txt");
   populateFile(90000, file);

   // Read the data from the file and flesh out the BST.
//    BinarySearchTree b;
//    readFileAndBuildBST(file, b);
}
int main()
{
    driver();
}