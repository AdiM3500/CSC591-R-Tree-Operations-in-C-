




//case 1: We do a range search of a search rectangle that does not overlap any MBRs in an R-Tree of height 2
//case 2: We do a range search of a degenerate search ractangle in an R-tree of height 2.
//case 3: We do a range search of a search rectangle that spans a single MBR in a tree of height 2.
//case 4: We do a range search of a search rectangle that spans the entire tree of height 2.
//case 5: We look for a search rectangle that partially overlaps 2 MBRs on a tree of height 2.
//case 6: We look for a search rectangle that spans the largest MBR in a tree of height 3.
//case 7: We look for a search rectangle that spans the entire tree of height 3.





//note: the range query will return all the datapoints are present within the search rectangle