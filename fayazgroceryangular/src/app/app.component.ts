import { Component } from '@angular/core';
import { AuthService } from './auth.service';
import { Router } from '@angular/router';
import { UserService } from './user.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  constructor(private userService: UserService, private auth: AuthService, router: Router){
    //Currently google has no direct working way of returning url
    //Everytime user logs in or logs out. if user logs out then no user object(null)
    auth.user$.subscribe(user => {
      //BUG FIX: Went to mananage products, hit refresh then set to homepage. In local
      //  storage is set to return to root of application
      //Solution: Delete returnURl once it is read only want to redirect first time when
      //  user is sent to google then need to return
      if(!user) return;

        userService.save(user);//Since we are not registering users
        //users may update name and email outside of our application
        //this service allows to get most up to date information.

        let returnUrl = localStorage.getItem('returnUrl');
        if(!returnUrl) return;
        
        localStorage.removeItem('returnUrl');
        router.navigateByUrl(returnUrl)
       
        
    })
  }
}
