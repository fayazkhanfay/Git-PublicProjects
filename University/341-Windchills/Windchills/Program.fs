//
//F# program to compute windchills
//
//<FAYAZ KHAN>
//U. of Illinois, Chicago
//CS 341, Fall 2015
//Homework 4 
//

#light

let windchill T W = 
  //let T = 10.0
  let WC = 35.7 + (0.6*T) - (35.7*System.Math.Pow(W,0.16)) + (0.43*T*System.Math.Pow(W,0.16))    
  WC

[<EntryPoint>]
let main argv = 
  printf "Please enter a temperature (degress F): "
  let input = System.Console.ReadLine()
  let T = System.Convert.ToDouble(input)

  let WS = [1.0 .. 20.0] //????how does it know to do 20 elements and not 40
  //let windchills = List.map windchill WS // Previously but we cant just add T to this but map only supplies one  
  let windchills  = List.map (fun W -> windchill T W) WS // now takes two paramaters and returns one 

  printfn "" //printfn goes to the next line, no n same line
  printfn "Windchills:"
  printfn "%A" windchills
  printfn ""

  0 


//#light // this enables indentation mode


//BIG NOTE: You must hit space twice or  configure visual "tab" to translate
//as two spaces

//[<EntryPoint>]
//let main argv = 
  //  let message = "Hello World!" //Their are no ";"
   // printfn "%A\n" message // shows new line and additional line
   // printfn "" //acts like "\n"
   // 0 // return an integer exit code

