# 10147

This question can be described as to find the minimal cost to build a connected graph. Since the graph is unidirectional, we can add all connected points into one set which represents a connectivity. Next, we should calculate the mutual distance between each two connectivity and push the values into a min-heap. After that, each time we choose the pair with minimal cost which decreases the number of connectivity exactly by one until there is only one connectivity left. And the selection sequence is an acceptable solution.
