{-# LANGUAGE OverloadedStrings #-}

module Main where

import System.Directory (doesDirectoryExist, getDirectoryContents, withCurrentDirectory)
import System.FilePath ((</>))
import System.Process (system)
import System.Exit
import System.Exit (exitFailure)
import System.Environment (getArgs)
import Control.Monad (when)

main :: IO ()
main = do
    args <- getArgs
    case args of
        [sourceDir, outputArchive] -> archiveWithSystem sourceDir outputArchive
        _ -> do
            putStrLn "Использование: program <папка> <архив.tar.gz>"
            exitFailure

archiveWithSystem :: FilePath -> FilePath -> IO ()
archiveWithSystem sourceDir outputArchive = do
    exists <- doesDirectoryExist sourceDir
    when (not exists) $ do
        putStrLn $ "Ошибка: папка не существует: " ++ sourceDir
        exitFailure
    
    putStrLn $ "Архивация: " ++ sourceDir
    let command = "tar -czf \"" ++ outputArchive ++ "\" -C \"" ++ sourceDir ++ "\" ."
    exitCode <- system command
    
    case exitCode of
        ExitSuccess -> putStrLn $ "✓ Готово: " ++ outputArchive
        ExitFailure code -> do
            putStrLn $ "Ошибка (код: " ++ show code ++ ")"
            exitFailure
