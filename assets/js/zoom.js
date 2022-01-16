let togg1 = document.getElementById("togg1");
let togg2 = document.getElementById("togg2");
let togg3 = document.getElementById("togg3");

let d1 = document.getElementById("cache");
let d2 = document.getElementById("cache2");
let d3 = document.getElementById("cache3");


togg1.addEventListener("click", () => {
  if(getComputedStyle(d1).display != "none"){
    d1.style.display = "none";
  } else {
    d1.style.display = "block";
  }
})

function togg(){
  if(getComputedStyle(d2).display != "none"){
    d2.style.display = "none";
  } else {
    d2.style.display = "block";
  }
};

function toggb(){
    if(getComputedStyle(d3).display != "none"){
      d3.style.display = "none";
    } else {
      d3.style.display = "block";
    }
};



togg2.onclick=togg; 
togg3.onclick=toggb; 
