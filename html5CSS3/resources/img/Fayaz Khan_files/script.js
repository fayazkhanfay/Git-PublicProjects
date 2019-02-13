/*Every js file starts with this. This only runs when the document is loaded */
$(document).ready(function(){

    /*
    jquery example
    $('h1').click(function(){
        //this refers to h1
        $(this).css('background-color', '#ff0000') //Changes background color to red
    })*/


    /*Sticky navigation */
    //direction is to detect if user is scrolling up or down to add or remove sticky nav
    $('.js--section-features').waypoint(function(direction){
        if(direction == 'down')
        {
            $('nav').addClass('sticky');
        }
        else{
            $('nav').removeClass('sticky');
        }
    }, {
        offset: '60px;'/*specifies when stick will add or be removed */
        });

    /*Scroll on buttons: when user clicks on button will jump to section with animation scroll*/
    $('.js--scroll-to-plans').click(function(){ //1000 is speed
        $('html, body').animate({scrollTop: $('.js--section-plans').offset().top},1000)
    });

    $('.js--scroll-to-start').click(function(){ //1000 is speed
        $('html, body').animate({scrollTop: $('.js--section-features').offset().top},1000)
    });

    /*Navigation Scroll: copy and pasted code below*/
    $(function() {
        $('a[href*=#]:not([href=#])').click(function() {
          if (location.pathname.replace(/^\//,'') == this.pathname.replace(/^\//,'') && location.hostname == this.hostname) {
            var target = $(this.hash);
            target = target.length ? target : $('[name=' + this.hash.slice(1) +']');
            if (target.length) {
              $('html,body').animate({
                scrollTop: target.offset().top
              }, 1000);
              return false;
            }
          }
        });
      });

    /*Animation on Scroll: as user scrolls up or down user will see animation */
    /* Animations on scroll: https://daneden.github.io/animate.css/ to get class */
    $('.js--wp-1').waypoint(function(direction) {
        $('.js--wp-1').addClass('animated fadeIn');
    }, {
        offset: '50%'
    });
    
    $('.js--wp-2').waypoint(function(direction) {
        $('.js--wp-2').addClass('animated fadeInUp');
    }, {
        offset: '50%'
    });
    
    $('.js--wp-3').waypoint(function(direction) {
        $('.js--wp-3').addClass('animated fadeIn');
    }, {
        offset: '50%'
    });
    
    $('.js--wp-4').waypoint(function(direction) {
        $('.js--wp-4').addClass('animated pulse');
    }, {
        offset: '50%'
    });

});