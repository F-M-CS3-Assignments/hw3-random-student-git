all:
	g++ -g -Wall TimeCode.cpp -o tct 
	g++ -g -Wall NasaLaunchAnalysis.cpp -o nasa
	g++ -g -Wall PaintDryTimer.cpp -o pdt


runtct:
	./tct

runnasa:
	./nasa

runpdt:
	./pdt
	
check:
	valgrind --leak-check=yes ./tct
	valgrind --leak-check=yes ./nasa
	valgrind --leak-check=yes ./pdt