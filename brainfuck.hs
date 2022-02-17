import System.Environment ( getArgs )
import Data.List

import Data.Map ( (!), empty, insert, member, Map, toList )

import Data.Char

import System.IO

run :: [Char] -> Int -> Map Int Int -> Int -> IO ()
run ops ip dat dp | ip >= length ops || ip < 0 = do
                                        return ()
                  | ops!!ip == '>' = run ops (ip+1) dat (dp+1)
                  | ops!!ip == '<' = run ops (ip+1) dat (dp-1)
                  | ops!!ip == '+' = run ops (ip+1) (Data.Map.insert dp (if Data.Map.member dp dat then dat ! dp + 1 else 1) dat) dp
                  | ops!!ip == '-' = run ops (ip+1) (Data.Map.insert dp (if Data.Map.member dp dat then dat ! dp - 1 else (-1)) dat) dp
                  | ops!!ip == '.' = do
                                        if Data.Map.member dp dat then putChar (chr (dat ! dp)) else putChar 'c'
                                        run ops (ip+1) dat dp
                  | ops!!ip == ',' = do
                                    ch <- getChar
                                    let num = ord ch
                                    run ops (ip+1) (Data.Map.insert dp num dat) dp
                  | ops!!ip == '[' = if not (Data.Map.member dp dat) || dat ! dp == 0 then do
                                                                                            let jmp = getJumpForward ops (ip+1) 1
                                                                                            run ops (jmp+1) dat dp
                                                                                      else run ops (ip+1) dat dp
-- otherwise == ops!!ip == ']'
                  | otherwise  = if Data.Map.member dp dat && dat ! dp /= 0 then do
                                                                    let jmp = getJumpBackward ops (ip-1) (-1)
                                                                    run ops (jmp+1) dat dp
                                                                else run ops (ip+1) dat dp

getJumpForward :: [Char] -> Int -> Int -> Int 
getJumpForward ops ip count 
                            | count /= 0 = if ops !! ip == '[' then getJumpForward ops (ip+1) (count+1) else if ops !! ip == ']' then getJumpForward ops (ip+1) (count-1) else getJumpForward ops (ip+1) count
                            | otherwise  = ip-1
getJumpBackward :: [Char] -> Int -> Int -> Int 
getJumpBackward ops ip count 
                             | count /= 0 = if ops !! ip == '[' then getJumpBackward ops (ip-1) (count+1) else if ops !! ip == ']' then getJumpBackward ops (ip-1) (count-1) else getJumpBackward ops (ip-1) count
                             | otherwise  = ip+1

main :: IO ()
main = do
    args <- getArgs
    instream <- readFile (head args)
    let instructions = Data.List.filter (`elem` "<>+-.,[]") instream
    --print instructions
    run instructions 0 Data.Map.empty 0
    