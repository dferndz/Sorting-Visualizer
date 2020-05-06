# Sorting
Visual sorting algorithms<br>

This is an educational software that graphically shows how several sorting algorithms work. <br>
You can add your own sorting algorithms following the instructions Adding custom sorting algorithm section.

<img src="https://github.com/dferndz/Sorting/blob/master/Screenshot.png?raw=true">

<hr>
<h3>Adding custom sorting algorithm:</h3>
<pre>

Write the sorting function in Program.cpp
The function data type MUST be void, and MUST take one and ONLY ONE parameter of type std::vector&lt;int&gt;*.


Add delay using std::this_thread::sleep_for(std::chrono::milliseconds(DELAY)); for every comparisson.
Add final delay using std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_2)); before exiting the function.

Set green = [index_number]; to highlight a bar
Set red = [index_number]; to highlight a bar

</pre>
