import System.Random
import qualified Data.List as List

target :: String
target = "Hello World"

-- Create a random individual
createIndividual :: StdGen -> (String, StdGen)
createIndividual gen =
  let (randomChars, newGen) = foldr generateRandomChar ([], gen) [1..length target]
  in (randomChars, newGen)
  where
    generateRandomChar :: a -> ([Char], StdGen) -> ([Char], StdGen)
    generateRandomChar _ (chars, g) =
      let (randInt, newGen) = randomR (0, charSetSize - 1) g :: (Int, StdGen)
      in (charSet !! randInt : chars, newGen)

-- Create a population of individuals
createPopulation :: Int -> StdGen -> ([String], StdGen)
createPopulation size gen =
  foldr generateIndividual ([], gen) [1..size]
  where
    generateIndividual :: a -> ([String], StdGen) -> ([String], StdGen)
    generateIndividual _ (population, g) =
      let (individual, newGen) = createIndividual g
      in (individual : population, newGen)

-- Calculate the fitness of an individual
fitnessFunction :: String -> Int
fitnessFunction individual =
  sum $ zipWith (\a b -> if a == b then 1 else 0) target individual

-- Select parents from the population
selectParents :: [String] -> StdGen -> ([String], StdGen)
selectParents population gen =
  let fitnesses = map fitnessFunction population
      totalFitness = sum fitnesses
      probabilities = map (\fitness -> fromIntegral fitness / fromIntegral totalFitness) fitnesses
      (index1, newGen1) = weightedRandomChoice probabilities gen
      (index2, newGen2) = weightedRandomChoice probabilities newGen1
  in ([population !! index1, population !! index2], newGen2)

-- Helper function for weighted random choice
weightedRandomChoice :: [Float] -> StdGen -> (Int, StdGen)
weightedRandomChoice weights gen =
  let (randVal, newGen) = random gen :: (Float, StdGen)
      cumulativeWeights = List.scanl (+) 0 weights
      index = findIndex randVal cumulativeWeights
  in (index, newGen)

-- Find the index where the cumulative weight exceeds the random value
findIndex :: Float -> [Float] -> Int
findIndex randVal cumulativeWeights =
  case dropWhile (<= randVal) cumulativeWeights of
    [] -> length cumulativeWeights - 1
    (x:_) -> List.findIndex (==x) cumulativeWeights

-- Perform crossover between two parents
crossover :: String -> String -> Float -> StdGen -> (String, StdGen)
crossover parent1 parent2 crossoverRate gen =
  if randVal < crossoverRate
  then
    let crossoverPoint = randomR (0, length target - 1) :: StdGen -> (Int, StdGen)
        (point, newGen) = crossoverPoint gen
    in (take point parent1 ++ drop point parent2, newGen)
  else
    (if randomBool gen then parent1 else parent2, gen)
  where
    (randVal, _) = random gen :: (Float, StdGen)

-- Helper function for random boolean value
randomBool :: StdGen -> Bool
randomBool gen =
  let (randInt, _) = randomR (0, 1) gen :: (Int, StdGen)
  in randInt == 1

-- Mutate an individual
mutate :: String -> Float -> StdGen -> (String, StdGen)
mutate individual mutationRate gen =
  foldr mutateChar ([], gen) [0..length individual - 1]
  where
    mutateChar :: Int -> ([Char], StdGen) -> ([Char], StdGen)
    mutateChar index (mutatedChars, g) =
      if randVal < mutationRate
      then
        let (randInt, newGen) = randomR (0, charSetSize - 1) g :: (Int, StdGen)
        in (charSet !! randInt : mutatedChars, newGen)
      else
        (individual !! index : mutatedChars, g)
      where
        (randVal, _) = random g :: (Float, StdGen)

-- Run the genetic algorithm
geneticAlgorithm :: Int -> Int -> Float -> Float -> StdGen -> IO ()
geneticAlgorithm populationSize generations mutationRate crossoverRate initialGen = do
  let (initialPopulation, _) = createPopulation populationSize initialGen
  evolve initialPopulation 0 initialGen
  where
    evolve :: [String] -> Int -> StdGen -> IO ()
    evolve population generation gen
      | generation >= generations = putStrLn "Target not found"
      | target `elem` population = putStrLn $ "Target found in generation " ++ show generation ++ ": " ++ target
      | otherwise = do
          let sortedPopulation = List.sortBy (compare `on` (negate . fitnessFunction)) population
          putStrLn $ "Generation " ++ show generation ++ ": " ++ head sortedPopulation
          let (parentPair, newGen1) = selectParents population gen
              [parent1, parent2] = parentPair
              (child, newGen2) = crossover parent1 parent2 crossoverRate newGen1
              (mutatedChild, newGen3) = mutate child mutationRate newGen2
              newPopulation = take (populationSize - 1) sortedPopulation ++ [mutatedChild]
          evolve newPopulation (generation + 1) newGen3

-- Charset and its size
charSet :: String
charSet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "

charSetSize :: Int
charSetSize = length charSet

-- Comparison function
on :: (Ord b) => (a -> b) -> a -> a -> Ordering
on f x y = compare (f x) (f y)

main :: IO ()
main = do
  gen <- getStdGen
  let populationSize = 100
      generations = 1000
      mutationRate = 0.01
      crossoverRate = 0.7
  geneticAlgorithm populationSize generations mutationRate crossoverRate gen