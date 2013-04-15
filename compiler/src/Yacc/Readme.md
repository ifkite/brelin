//the way i wanna to search table, is hash map
//wtite a naive one first
data structure:
basic_tab[] = {
	{S, E, 0}
}

prog
initialize:
1   .1 find the start identifer in table
	.2 set successive item
	.add the rule into stat (I0)

2	.1 finds the clusure set  of I0
		.1.1 find the n th(which n is showed by poperity 'pointer')
		     id
		.1.2 search table(property left, which is equal to id we found), find all rules that matchs, maybe we can mark down that rules, successive items of these rules will be changed;
		     changed them by his father rule
		.1.3 find the next identifer which follows in the parent rule, find the first set of that identifer , add them to successive items sets[1], or just falls in two another easier case, followed null or an terminal id
		.1.4 mark down the parent rules if all his son rules is checked[2]
		.1.5 handle son, until ...
		
3	.1 dect all id that after pointer, set up a tree, traversal this tree in breadth-first, each tree node bocome a rule stat




		2.1.3 find first set of identifer
			.1 find all rules which left id is equals to that  	
			.2 find the first character in right expression
			   .1 when with | ; , it implies that it follow with the termination

			 [1] how to add, check the successive items 
		2.1.4 if not, handle his son rules 
		2.1.5 how until , how to terminate


--------------------------------------------------------------------
a strick input format more than ever:
1.every id should be in the sets 
2.; end
3.no |
4.left=>right
5.every id should be presented by one character
6.digit would be id if you like
7.no space
