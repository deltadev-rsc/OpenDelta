/*
  переписываю dexide из dltsh с си на растик.
*/
use std::fs::File;
use std::io::{BufRead, BufReader};
use std::io;

const MAX_LINES: usize = 512;
const MAX_LINE_LENGTH: usize = 1024;

pub fn editor_logo() {
    println!("████████        ███████     █       █   ██  ████████        ███████    ");
    println!("██     ██      ██     ██    ██     ██       ██     ██      ██     ██   ");
    println!("██      ██    ██       ██    ██   ██    ██  ██      ██    ██       ██  ");
    println!("██       ██  ██         ██    █████     ██  ██       ██  ██         ██ ");
    println!("██       ██  █████████████   ██   ██    ██  ██       ██  █████████████ ");
    println!("██      ██    ██            ██     ██   ██  ██      ██    ██           ");
    println!("█████████      ██████████   █       █   ██  █████████      ██████████  ");
}

pub fn main() -> io::Result<()> {
    println!("welcome to Dexide!");
    editor_logo();

    let mut lines: Vec<String> = Vec::new(); //: [[char; MAX_LINE_LENGTH]; MAX_LINES];
    let mut file_name = String::new();
    let mode: char;
    let mut line_count: usize = 0;

    println!("input file name to edit: ");
    io::stdin()
        .read_line(&mut file_name)
        .expect("[err]: [failed to read file name]");
    file_name = file_name.trim().to_string();

    let file = File::open(&file_name)?;
    let reader = BufReader::new(file);

    for line in reader.lines() {
        if line_count >= MAX_LINES {
            break;
        }
        lines.push(line?);
        line_count += 1;
    }

    Ok(())
}
