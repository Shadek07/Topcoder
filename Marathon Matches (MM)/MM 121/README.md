## My Approach

My approach was to use Simulated Annealing(SA) technique where max. number of iterations was set to 4000. Before the first iteration of SA, I initialized results of all pairwise teams score through simulation. Then in every iteration of SA, I chose two random teams and calculated the game score through simulation if they played together. Then, through a custom euclidean weighted cost function, I either included the change of aforementioned two teams score in optimal solution or not.

My final position in this match was 41 out of total 57 coders who submitted code.
