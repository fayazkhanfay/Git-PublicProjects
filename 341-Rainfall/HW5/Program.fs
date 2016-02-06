//
// F# program to analyze rainfall data
// <<FAYAZ KHAN>>
// U. of Illinois, Chicago
// CS341, Fall 2015
// Homework 5
// 

#light

//
// ReadFile: reads a file line by line, returning a list
// of strings, one per line.
//

let ReadFile filename = 
  [ for line in System.IO.File.ReadLines(filename) -> line ]


//
// ParseLine: given a line from the rainfall file, parses this
// string into list of double values starting with the year, error
// rate, and then the 12 rainfall values (one per month).
//
let ParseLine (line:string) = 
  let strings = line.Split('\t')
  let strlist = Array.toList(strings)
  let values  = List.map (fun x -> System.Double.Parse(x, System.Globalization.NumberFormatInfo.InvariantInfo)) strlist
  values


//
// Given a year of data as a list of double values, outputs the year,
// error rate, and then the 12 rainfall values for each month.
//
let PrintOneYearOfData (values: double list) =
  printfn "%A: err=%A, %A" (int values.Head) values.Tail.Head values.Tail.Tail


//
// Task 1:
// print out the average rainfall for each year
//
let rec AvgPerYr( values: 'a list list)= //'a infers the type but we are also helping along with list list
  if values = [] then
    printf ""
  else                      ///values.Head.Tail.Tail because we wanted to take average everything after the error stats
    let avg = List.average values.Head.Tail.Tail  // List.average calculates avegrage of to the right 
    printfn"%A: %A" (int values.Head.Head) avg    //Print the year because we only want one value  and printing average
    AvgPerYr(values.Tail)                         //recurses back into it but sending the next spot in the list 


//
// Task 3 functions 
// 


// Finds the max and returns the max in the whole list 
let rec maxRainfall( values: 'a list list, max_ : 'a , yearRow : 'a list)= 
  if values = [] then
    [max_] @ yearRow  // sent both together max is the max yearRow is the entire row
  else                //purpose of this is because in .findIndex if not present will crash so has to be in row 
    let tempMax = List.max values.Head.Tail.Tail   // compares the values 
    if tempMax > max_ then
      maxRainfall (values.Tail, tempMax, values.Head)   //Updates the max
    else
      maxRainfall (values.Tail, max_, yearRow)          // Keeps the max the same 


// Finds the min and returns the min in the whole list
//Same notes as above 
let rec minRainfall( values: 'a list list, min_ : 'a, yearRow : 'a list)= 
  if values = [] then
    [min_] @ yearRow
  else 
    let tempMin = List.min values.Head.Tail.Tail
    if tempMin < min_ then
      minRainfall (values.Tail, tempMin, values.Head)
    else
      minRainfall (values.Tail, min_, yearRow)

//This works for either min or max because it is in rowM matching it to find in the index 
let dispAvg(rowM : 'a list) =
    let index = (List.findIndex (fun x -> x = rowM.Head) rowM.Tail) - 1  //To match the month 
    printfn" rainfall:  %A, %A/%A " rowM.Head index (int rowM.Tail.Head)
    
//
// END of TASK 3 functions 


//
//TASK 2 
//Calculate the monthly average for each month and also displays the results
let rec MonthAvg (dates : string list, length : 'a, index : 'a, values: float list list, oriValues : float list list, sumRec : float) =
  if index = 12 then // Becasue we have 12 months 
    printf""
  else if values = [] then
    let theAvg = sumRec/(float length) //length had to be casted because sumRec is an int 
    printfn"%s: %A " (dates.Item index) theAvg  
    MonthAvg (dates, length ,index+1, oriValues, oriValues,0.0)  //incrementing to the right and starting from begining of rec
  else
    let sumRec2 = sumRec + (List.nth values.Head.Tail.Tail index)   //keeps on adding all the values 
    MonthAvg (dates, length, index, values.Tail,oriValues, sumRec2) // keeps on rec downwards 
  
//
// Main:
//
[<EntryPoint>]
let main argv = 
  printfn "** Rainfall Analysis Program **"
  printfn ""

  //
  // read entire file as list of strings:
  //
  let file = ReadFile "rainfall-midway.txt"

  //
  // Parse the data into a list of lists, where
  // each sub-list is [year err value value ...]:
  //
  let rainfall = List.map ParseLine file

  //function call for calculating and printing avg rainfall per year 
  AvgPerYr rainfall
  printfn ""

  let Dates = ["Jan" ; "Feb" ; "Mar" ; "Apr" ; "May" ; "Jun" ; "Jul" ; "Aug" ; "Sep" ; "Oct" ; "Nov" ; "Dec"]
  MonthAvg(Dates, rainfall.Length,0, rainfall, rainfall, 0.0)

  let foundMax = maxRainfall(rainfall, 0.0, rainfall.Head)
  let foundMin = minRainfall(rainfall, foundMax.Head, rainfall.Head)  //I am sending foundMax as a paramater because i need an upperbound
  
  printfn"" 
  printf"Max"
  dispAvg(foundMax)

  printf"Min"
  dispAvg(foundMin)

  // done
  printfn ""
  printfn "** Done **"
  printfn ""
  printfn ""
  0 // return 0 => success
