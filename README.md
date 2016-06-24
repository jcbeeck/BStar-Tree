# BStar-Tree
"In computer science, B* (pronounced "B star") is a best-first graph search algorithm that finds the least-cost path from a given initial node to any goal node (out of one or more possible goals).

"The algorithm stores intervals for nodes of the tree as opposed to single point-valued estimates. Then, leaf nodes of the tree can be searched until one of the top level nodes has an interval which is clearly "best.""

Ref: https://en.wikipedia.org/wiki/B*

The main goals of the B family-trees (index files in DBMS) are:
- Sorted Intermediary and leaf nodes: Since it is a balanced tree, all nodes should be sorted.
- Fast traversal and Quick Search: One should be able to traverse through the nodes very fast. That means, if we have to  search for any particular record, we should be able pass through the intermediary node very easily.  This is achieved by sorting the pointers at intermediary nodes and the records in the leaf nodes. Any record should be fetched very quickly.  This is made by maintaining the balance in the tree and keeping all the nodes at same distance.
- No overflow pages.

Ref: https://www.tutorialcup.com/dbms/b-tree.htm

Source code deployed in April-2005 by the authors (Oscar Cuadros Linares and Jan Beeck) of this respository.
