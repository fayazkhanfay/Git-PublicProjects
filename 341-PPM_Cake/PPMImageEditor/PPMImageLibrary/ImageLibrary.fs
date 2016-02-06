//
//F#-based PPM image library.
//
//<<FAYAZ KHAN>>
//U. of Illinois, Chicago
//CS341, Fall 2015
//Homework 6
//

//Zoom and Threshood does not work but everything else does work

module PPMImageLibrary

#light


//
// DebugOutput:
//
// Outputs to console, which appears in the "Output" window pane of
// Visual Studio when you run with debugging (F5).
//
let rec private OutputImage(image:int list list) = 
  if image = [] then
    printfn "**END**"
  else
    printfn "%A" image.Head
    OutputImage(image.Tail)
           
let DebugOutput(width:int, height:int, depth:int, image:int list list) =
  printfn "**HEADER**"
  printfn "W=%A, H=%A, D=%A" width height depth
  printfn "**IMAGE**"
  OutputImage(image)


//
// TransformFirstRowWhite:
//
// An example transformation: replaces the first row of the given image
// with a row of all white pixels.
//
let rec BuildRowOfWhite cols white = 
  if cols = 0 then
    []
  else 
    // 1 pixel, i.e. RGB value, followed by remaining pixels:
    white :: white :: white :: BuildRowOfWhite (cols-1) white

let FirstRowWhite(width:int, height:int, depth:int, image:int list list) = 
  // first row all white :: followed by rest of original image
  (BuildRowOfWhite width depth) :: image.Tail




//Below methods is used for P3Image -----------------------------------------

let addSpace(sNumb: string list) = 
  List.reduce(fun x y -> x + " " + y )sNumb


let intToString(image: int list list) = //not going to recurse because we iterating through the list 
  List.map( fun down -> List.map(fun right -> right.ToString()) down) image
  |> List.map addSpace


//
// WriteP3Image:
//
// Writes the given image out to a text file, in "P3" format.  Returns true if successful,
// false if not.
//
let rec WriteP3Image(filepath:string, width:int, height:int, depth:int, image:int list list) = 
  //
  // Here's one possible strategy: build a list of strings, then WriteAllLines.
  // Each string appears on a separate line. 
  //
  //let L = ["Hello"; "World"; "1 2 3"; "10 20 30"]
  let L = ["P3"] @ [System.Convert.ToString(width); System.Convert.ToString(height) ]
          @[System.Convert.ToString(depth)]@(intToString image)
  System.IO.File.WriteAllLines(filepath, L)
  //
  true  // success

//End of P3 methods ----------------------------------------------------------------------

//Start Threshold--------------------------------------------------------------------------

     //Threshold(width:int, height:int, depth:int, image:int list list, threshold:int)
//let Threshold(width:int, height:int, depth:int, image:int list list) = 
  //List.map makeThres image

//END ThresHold ------------------------------------------------------------


//Start of GrayScale -----------------------------------------------------------------
let rec makeGray(image) =
  match image with
  | [] -> []    
  | _  -> let average = (image.Head + image.Tail.Head + image.Tail.Tail.Head)/3 //three values
          average::average::average::makeGray(image.Tail.Tail.Tail)// looks like 116 116 116 List(3 spot over)....

//GrayScale take the avg and then write the avg into everything 
let Grayscale(width:int, height:int, depth:int, image:int list list) = 
  //Dont worry about width height and depth not needed here but not allowed to modify
  //  I also got rid of the rec 
  List.map makeGray image

//END OF GrayScale-------------------------------------------------------------------------

//Start Flip Horizontal -----------------------------------------------------------

let rec FlipRowHor imageN image =
  match image with 
  | [] -> imageN
  | _  -> FlipRowHor (image.Head::image.Tail.Head::image.Tail.Tail.Head::imageN) image.Tail.Tail.Tail
  

let FlipHorizontal(width:int, height:int, depth:int, image:int list list) = 
  List.map(FlipRowHor []) image
  

//END Flip Horizontal --------------------------------------------------

//Start RotateRight90--------------------------------------------------------------

let rec PtoRGB L = 
  match L with
  | [] -> []
  | (r,g,b)::tail -> [r;g;b] @ PtoRGB tail


let combine image1 image2 =
  List.map2 (fun x y -> x @ y) image1 image2

let rec Rotate1R image = 
  match image with 
  | [] -> []
  | sample::tail -> [sample] :: Rotate1R tail

let rec RotateP image = 
  match image with
  | [ ]   -> []
  | test::[] -> Rotate1R test
  |  _    -> combine (RotateP image.Tail) (Rotate1R image.Head)


let rec RGBtoP image = 
  match image with
  | [] -> []
  | r::g::b::tail -> (r,g,b) :: RGBtoP tail


let RotateRight90(width:int, height:int, depth:int, image:int list list) = 
  List.map RGBtoP image   
  |> RotateP              
  |> List.map PtoRGB      


//END RotateRight90-------------------------------------------------------------------









let rec Zoom(width:int, height:int, depth:int, image:int list list, factor:int) = 
  image

