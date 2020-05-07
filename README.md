# Sorting
Visual sorting algorithms<br>

This is an educational software that graphically shows how several sorting algorithms work. <br>
You can add your own sorting algorithms following the instructions Adding custom sorting algorithm section.<br>

<a href="https://dferndz.github.io/Sorting/Releases.html">Downloads</a>

<img src="https://github.com/dferndz/Sorting/blob/master/Screenshot.png?raw=true"><br><br>

<hr>
<h3>Dependencies</h3>

-SDL2.0<br>
-SDL_ttf<br>

<hr>
<h3>Adding custom sorting algorithm:</h3>

Write the sorting function in Program.cpp
The function data type MUST be void, and MUST take one and ONLY ONE parameter of type std::vector&lt;int&gt;*.

Your sorting function MUST set the flag Visualizer::getSorted() = true; before exiting. This flag tells the Visualizer the sorting is finished, so that it can go to the next sorting function.<br><br>

<strong>In the function body, use the following flags to interact with the visualizer:</strong><br><br>

<pre>
Visualizer::getGreen() = [some integer]; //[some integer] index in the array will be rendered green<br>
Visualizer::getRed() = [some integer];   //[some integer] index in the array will be rendered red<br>
Visualizer::getItr()++; //this increases the comparisson count in the visualizer<br>
Visualizer::sleep(); //sleep used every time the function does a comparisson<br>
Visualizer::sleep_final(); //sleep used at the end of the function, to allow the user to visualize the sorted data<br><br>
</pre>

<strong>To add your sorting algorithm to the visualizer:</strong><br><br>
Use: Visualizer::AddAlgorithm(functionName, "Algorithm Name", parameters);<br><br>

This is an example:
<pre>
Visualizer::AddAlgorithm(quickSort, "Quick Sort", PARAMETERS(
		5,		//bar width
		10,		//bar height scale
		160,	//number of elements in array
		50,		//max number generated for the array
		3,		//delay
		2000	//final delay
	));
  </pre>
  Or use Visualizer::GetParameters(); to get the default parameters.<br><br>
  Finally, call Visualizer::Init(); to start the visualization. <br><br>
  Go to Sorting/src/Program.cpp to see a functional example.
  
