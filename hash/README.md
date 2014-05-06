Introduce
=========
Hash table is a data structure used to implement an associative array, a structure 
that can map keys to values.

	index = f(key, array_size)

Often this is done in two steps:

	hash = hashfunc(key)
	index = hash % array_size

a classic applicate is used for dict searching.

Collision resolution
====================
1. Separate chaining

2. Open addressing

3. 2-choice hashing

Features
=========
1. Advantages

	1). fast, insert and find operation use O(1)

2. Drawbacks

Uses
====
1. symbol table, use on compiler

2. spell checking

3. caches

Reference
=========
* [Has table wikipedia](http://en.wikipedia.org/wiki/Hash_table)
* [hash.c](https://gist.github.com/tonious/1377667)
* [uthash](http://uthash.sourceforge.net/)
* [Hash table](http://www.cnblogs.com/Anker/archive/2013/01/27/2879150.html)
* [Has table implement on c](http://www.cnblogs.com/xiekeli/archive/2012/01/13/2321207.html)
