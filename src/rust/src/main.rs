use std::env;
use std::char;
use std::io::Read;

use std::fs;

fn read_file(filename: String) -> String  {
    
    let data: String = fs::read_to_string(filename).expect("");
    
    return data.chars().filter(|c| "+-.,<>[]".contains(*c)).into_iter().collect::<String>();
}

fn main() -> std::io::Result<()>{
    let args: Vec<String> = env::args().collect();

    if args.len() != 2 {
        println!("Expected file input");
        return Ok(());
    }
    let filename = &args[1];
    
    let instructions: String = read_file(filename.to_string());

    if instructions == "" {
        return Ok(());
    }

    let mut ip: usize = 0;
    let mut dp: usize = 0;
    
    //let mut data: Vec<i32> = Vec::new();  // An empty vector of i32s.


    let mut data: Vec<u32> = vec![0; 10000];
    
    let op_vector: Vec<char> = instructions.chars().collect();

    while ip < instructions.len() {
        let op: char = op_vector[ip];


        if op == '>' {
            dp += 1;
        } else if op == '<' {
            dp -= 1;
        } else if op == '+' {
             data[dp] += 1
        } else if op == '-' {
             data[dp] -= 1
        } else if op == '.' {
            let c = char::from_u32(data[dp]);
            print!("{}", c.expect(""));
        } else if op == ',' {
            let input: Option<u32> = std::io::stdin().bytes().next().and_then(|result| result.ok()).map(|byte| byte as u32);
            data[dp] = input.expect("");
        } else if op == '[' {
            if data[dp] == 0 {
                let mut count: usize = 1;
                while count != 0 {
                    ip += 1;
                    if op_vector[ip] == '[' {
                        count += 1;
                    }
                    else if op_vector[ip] == ']' {
                        count -= 1;
                    }
                } 
            }
        } else if op == ']' {
            if data[dp] != 0 {
                let mut count: usize = 1;
                while count != 0 {
                    ip -= 1;
                    if op_vector[ip] == '[' {
                        count -= 1;
                    }
                    else if op_vector[ip] == ']' {
                        count += 1;
                    }
                }
            }
        }
        ip += 1;
    }

    
    Ok(())

}

