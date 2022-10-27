use std::env;
use std::fs::File;
use std::io::BufReader;
use std::char;
use std::convert::TryInto;
use std::io::Read;


fn main() -> std::io::Result<()>{
    let args: Vec<String> = env::args().collect();

    if args.len() != 2 {
        println!("Expected file input");
        return Ok(());
    }
    let filename = &args[1];
    //println!("{:?}", filename);
    let file = File::open(filename)?;
    let mut buf_reader = BufReader::new(file);
    let mut instructions = String::new();
    buf_reader.read_to_string(&mut instructions)?;
    //println!("{}", instructions);
    instructions = instructions.chars().filter(|c| "+-.,<>[]".contains(*c)).into_iter().collect::<String>();
    
    //println!("{}", instructions);
    //println!("{}", instructions.len());
    let mut ip: i32 = 0;
    let mut dp: i32 = 0;
    
    //let mut data: Vec<i32> = Vec::new();  // An empty vector of i32s.

    let mut data: Vec<i32> = vec![0; 10000];
    

    while ip < instructions.len().try_into().unwrap() {
        let cc: usize = ip.try_into().unwrap();
        let di: usize = dp.try_into().unwrap();
        let op: char = instructions.chars().nth(cc).unwrap();


        if op == '>' {
            dp += 1;
        } else if op == '<' {
            dp -= 1;
        } else if op == '+' {
             data[di] += 1
        } else if op == '-' {
             data[di] -= 1
        } else if op == '.' {
            let c = char::from_u32(data[di].try_into().unwrap());
            print!("{}", c.expect(""));
        } else if op == ',' {
            let input: Option<i32> = std::io::stdin().bytes().next().and_then(|result| result.ok()).map(|byte| byte as i32);
            data[di] = input.expect("");
        } else if op == '[' {
            if data[di] == 0 {
                let mut count: usize = 1;
                while count != 0 {
                    ip += 1;
                    if instructions.chars().nth(ip.try_into().unwrap()).unwrap() == '[' {
                        count += 1;
                    }
                    else if instructions.chars().nth(ip.try_into().unwrap()).unwrap() == ']' {
                        count -= 1;
                    }
                } 
            }
        } else if op == ']' {
            if data[di] != 0 {
                let mut count: usize = 1;
                while count != 0 {
                    ip -= 1;
                    if instructions.chars().nth(ip.try_into().unwrap()).unwrap() == '[' {
                        count -= 1;
                    }
                    else if instructions.chars().nth(ip.try_into().unwrap()).unwrap() == ']' {
                        count += 1;
                    }
                }
            }
        }
        ip += 1;
    }

    
    Ok(())

}

