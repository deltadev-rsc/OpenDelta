use std::io;

fn main() {
    println!("[КАЛЬКУЛЯТОР НА РАСТЕ]");

    let mut input: String = String::new();

    println!("[пишите как в обычной тетрадке(к примеру 4 + 5). допустимые операции: + - * /]");

    io::stdin()
        .read_line(&mut input)
        .expect("[err]: [ошибка чтения строки]");

    let mut parts = input.split_whitespace();
    
    let first_num: f64 = match parts.next() {
        
        Some(num) => match num.parse() {
            Ok(n) => n,
            Err(_) => {
                eprintln!("[err]: [invalid input for the first number]");
                return;
            }
        },
        
        None => {
            eprintln!("[err]: [no input provided for the first number]");
            return;
        }
    };

    let symbol: char = match parts.next() {
    
        Some(sym) => match sym.chars().next() {

            Some(c) => c,
            None => {
                eprintln!("[err]: [invalid input for the symbol operation]");
                return;
            }
        },
    
        None => {
            eprintln!("[err]: [no input provide for the fymbol operation]");
            return;
        }
    };

    let second_num: f64 = match parts.next() {
        
        Some(num) => match num.parse() {

            Ok(n) => n,
            Err(_) => {
                eprintln!("[err]: [invalid input for the second number]");
                return;
            }
        },

        None => {
            eprintln!("[err]: [no input provider for the second number]");
            return;
        }
    };

    let res = match symbol {
        '+' => Some(first_num + second_num),
        '-' => Some(first_num - second_num),
        '*' => Some(first_num * second_num),
        '/' => Some({
            if second_num == 0.0 {
                eprintln!("[err]: [division by ZERO]");
                return; 
            }
            else {
                Some(first_num / second_num)
            }
        }.expect("REASON")),

        _ => {
            eprintln!("[err]: [invalid operation symbol]");
            return;
        }
    };

    if let Some(reuslt) = res { 
        println!("result: {:?}", res);
    }
}
