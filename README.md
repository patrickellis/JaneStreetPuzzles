Jane Street Puzzles
======
<a href="https://www.patrickellis.dev/all/projects/janestreet-puzzles" target="_blank"> View the project page on my site </a>
## Description
This repository serves to hold all of my solutions to the Jane Street Puzzles that I have solved thus far. I absolutely love how challenging (and rewarding) some of these puzzles have been, and as of the time of writing this comment (2021/04) I am continuing to adore the process of tackling some of the more difficult problems hosted by this hedge fund. 

<p align="center">
  <img src = "https://github.com/patrickellis/Portfolio/blob/master/images/docs/chessalgohuman.gif" style="padding-top:100px; width:350px;height:350px;" width="650" />
</p>

## Puzzle Solving
I wanted a practical use for the program other than playing versus AI programs and other players, so I adapted the use case to be able to begin playing from any position - assuming it is our turn to play. 
This means that the bot can solve puzzles dynamically on almost any website.

<p align="center">
  <img src = "https://github.com/patrickellis/Portfolio/blob/master/images/docs/chessalgopuzzle.gif" style="padding-top:100px; width:350px;height:350px;" width="650" />
</p>

## Artifical Intelligence
ChessAlgo involves a sequential pre-processing pipeline. The first step involves locating the board on the screen, done through (relatively) straightforward gradient analysis. 
The second step uses a neural network trained on many chessboard images to convert an image of a chessboard to its string representation to be passed to a chess engine for analysis. 
