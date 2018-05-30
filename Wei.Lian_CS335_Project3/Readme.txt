Wei Lian
CS335

1)This Hash-Map program completed all parts.

2)the bugs i found is :the program has issues with rehash function, it inserted to wrong spot after rehash function.

3)Tested with provided txt file and type command
./test_hash_map words.txt quadratic
./test_hash_map words.txt chaining
./test_hash_map words.txt double



4)input file input_part2a.txt
words.txt

Test Case:
Wei:Hash_map WilliamLian$ ./test_hash_map words.txt chaining
2861419085ns
2861ms
Please enter a word: 
live
the lists are : 
dive
five
give
hive
jive
lice
life
like
lime
line
love
wive
Please enter another word: 
like
the lists are : 
bike
hike
lake
lice
life
lime
line
live
luke
mike
pike

Wei:Hash_map WilliamLian$ ./test_hash_map words.txt quadratic
2927645238ns
2927ms
Please enter a word: 
pink
the lists are : 
fink
kink
link
mink
pick
pine
ping
pint
punk
rink
sink
wink
Please enter another word: 
eye
the lists are : 
aye
bye
dye
eke
ere
eve
ewe
lye
rye
Wei:Hash_map WilliamLian$ ./test_hash_map words.txt double
2862878191ns
2862ms
Please enter a word: 
sea
the lists are : 
lea
pea
sec
see
sen
seq
set
sew
sex
spa
tea
yea
Please enter another word: 
ocrean
the lists are : 