push:
	git push origin master
commit:
	git commit -a -m "Third Commit"
anagram:
	gcc uni/Week5/timeKiller.c -std=c90 -pedantic -Wall -Wextra -o uni/Week5/timeKiller.out
	uni/Week5/timeKiller.out compiler "uni/Week5/eowl_english_words.txt"


compileC:
	gcc uni/Week4/COMPLETE/lifewar.c -std=c90 -pedantic -Wall -Wextra -o uni/Week4/COMPLETE/lifewar.out
compileG:
	gcc uni/Week4/GOL/GOL.c -std=c90 -pedantic -Wall -Wextra -o uni/Week4/GOL/GOL.out
war:
	uni/Week4/COMPLETE/lifewar.out uni/Week4/COMPLETE/best1.lif uni/Week4/COMPLETE/best2.lif
clonewar:
	uni/Week4/COMPLETE/lifewar.out uni/Week4/COMPLETE/best1.lif uni/Week4/COMPLETE/best2.lif
life:
		uni/Week4/GOL/GOL.out uni/Week4/COMPLETE/best2.lif uni/Week4/COMPLETE/best1.lif
flife:
		./a.out uni/Week4/COMPLETE/best1.lif uni/Week4/COMPLETE/best2.lif
proflifer:
		gprof a.out
fast:
		gcc  -Wall -c -pg uni/Week4/COMPLETE/lifewar.c
		gcc  -Wall -pg uni/Week4/COMPLETE/lifewar.o

1-1:
	gcc uni/Week1/Exc-1.02.c -o uni/Week1/Exc-1.02.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week1/Exc-1.02.out

1-2:
	gcc uni/Week1/Exc-1.03.c -o uni/Week1/Exc-1.03.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week1/Exc-1.03.out
1-3:
	gcc uni/Week1/Exc-1.03-b.c -o uni/Week1/Exc-1.03-b.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week1/Exc-1.03-b.out

1-4:
	gcc uni/Week1/Exc-2.11.c -o uni/Week1/Exc-2.11.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week1/Exc-2.11.out

1-5:
	gcc uni/Week1/Exc-2.17.c -o uni/Week1/Exc-2.17.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week1/Exc-2.17.out
1-6:
	gcc uni/Week1/Exc-3.01.c -o uni/Week1/Exc-3.01.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week1/Exc-3.01.out
1-7:
	gcc uni/Week1/Exc-3.15.c -o uni/Week1/Exc-3.15.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week1/Exc-3.15.out
1-8:
	gcc uni/Week1/Exc-4.10.c -o uni/Week1/Exc-4.10.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week1/Exc-4.10.out
1-9:
	gcc uni/Week1/Exc-4.12.c -o uni/Week1/Exc-4.12.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week1/Exc-4.12.out
1-10:
	gcc uni/Week1/Exc-5.11.c -o uni/Week1/Exc-5.11.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week1/Exc-5.11.out
1-11:
	gcc uni/Week1/Exc-6.03.c -o uni/Week1/Exc-6.03.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week1/Exc-6.03.out
1-12:
	gcc uni/Week1/Exc-7.03.c -o uni/Week1/Exc-7.03.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week1/Exc-7.03.out

2-1:
	gcc uni/Week2/planTrium.c -o uni/Week2/planTrium.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week2/planTrium.out

2-3:
	gcc uni/Week2/HSeq.c -o uni/Week2/HSeq.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week2/HSeq.out

3-1:
	gcc uni/Week3/Palindrome.c -o uni/Week3/Palindrome.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week3/Palindrome.out


3-3-X:
	gcc uni/Week3/Roman.c -o uni/Week3/Roman.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week3/Roman.out X
3-3-I:
	gcc uni/Week3/Roman.c -o uni/Week3/Roman.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week3/Roman.out I
3-3-XI:
	gcc uni/Week3/Roman.c -o uni/Week3/Roman.out -pedantic -Wall -Wextra -std=c90 -lm
	uni/Week3/Roman.out XI
