# Objective
- To create a simple map application that allows users to find the shortest path, minimum cost path, and minimum time elapsing path between two cities on the map.
# Abstract
- Dijkstra's algorithm is a popular graph algorithm that efficiently finds the shortest path in a weighted graph. It works by iteratively selecting the vertex with the minimum distance and updating the distances of its neighbouring vertices. In this application, Dijkstra's algorithm is applied to the city matrix, considering the distances as the edge weights and time and costs as additional constraints.
- The map application provides functionalities to display the city map, find the shortest path, find the minimum time elapsed path and calculate the minimum cost between a given source city and destination city. The shortest path is determined based on the minimum distance, and in case of multiple paths with the same distance, the minimum time is considered.
- By using Dijkstra's algorithm, the application can efficiently solve the problem of finding the shortest path, minimum time elapsed path and minimum cost between cities. It allows users to explore different routes and make informed decisions based on distance, time and cost factors.
# Getting Started
- This project contains vs_code configuration files within ".vscode/", used to provide arguments to the compiler.
- ".vscode/tasks.json" contains development and production arguments, which can be changed accordingly.
- Arguments for development are enabled by default. Which can be disabled on production.

