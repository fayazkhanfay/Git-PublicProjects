import { Injectable } from '@angular/core';
import { AngularFireAuth } from 'angularfire2/auth';
import * as firebase from 'firebase';
import {Observable} from 'rxjs/Observable';
import { ActivatedRoute } from '@angular/router';
import { AppUser } from './models/app-user';
import { UserService } from './user.service';
import 'rxjs/add/operator/switchMap';
import 'rxjs/add/observable/of';

@Injectable()
export class AuthService {
  //$ tells others it is a observable 
  user$: Observable <firebase.User>;


  constructor(
    private userService: UserService,
    private afAuth: AngularFireAuth, 
    private route: ActivatedRoute) {   
    
      //observable
    this.user$ = afAuth.authState
    //Always unsubscribe from firebase observables because of async data
    //could use ngOnDestroy but this implementation is cleaner 
   }

  login(){
    //this for reading params in url
    let returnUrl = this.route.snapshot.queryParamMap.get('returnUrl') || '/';
    localStorage.setItem('returnUrl', returnUrl);
    
    //implement oauth will redirect with oauth providers google,facebook...
    this.afAuth.auth.signInWithRedirect(new firebase.auth.GoogleAuthProvider())
  }

  logout(){
    this.afAuth.auth.signOut();
  }

  //Convert firebase Observable to AppUser observable
  get appUser$(): Observable<AppUser>{
    return this.user$ //user observable
    .switchMap(user => {  //switch to new observable returned from get method
      if (user) return this.userService.get(user.uid);

      return Observable.of(null);//if user logs out then returns null
    }); 
  }

}
