/*
  переписываю древний редактор dex из dltsh на rust
*/

use std::io;
use std::fs::File;
use std::io::Read;
use scanf::scanf;

const MAX_LINES: usize = 512;
const MAX_LINE_LENGTH: usize = 1024;

pub fn EditorLogo() {
    println!("████████        ███████     █       █   ██  ████████        ███████    ");
    println!("██     ██      ██     ██    ██     ██       ██     ██      ██     ██   ");
    println!("██      ██    ██       ██    ██   ██    ██  ██      ██    ██       ██  ");
    println!("██       ██  ██         ██    █████     ██  ██       ██  ██         ██ ");
    println!("██       ██  █████████████   ██   ██    ██  ██       ██  █████████████ ");
    println!("██      ██    ██            ██     ██   ██  ██      ██    ██           ");
    println!("█████████      ██████████   █       █   ██  █████████      ██████████  ");
}

pub fn main() {
    println!("welcome to Dexide!");
    EditorLogo();

    let lines: [[char; MAX_LINE_LENGTH]; MAX_LINES];
    let mut fileName: &str;
    let mode: char;
    let lineCount: i64;

    println!("input file name to edit: ");
    if scanf!("{fileName}").is_ok() {
        let mut file = File::create(fileName);
    }
    else {
        println!("[err]: [failed to create or open file to edit]");
    }
}
