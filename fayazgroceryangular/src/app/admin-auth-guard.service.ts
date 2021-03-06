import { Injectable } from '@angular/core';
import { CanActivate } from '@angular/router';
import { AuthService } from './auth.service';
import { UserService } from './user.service';

import { Observable } from 'rxjs/Observable';
import 'rxjs/add/operator/map';

@Injectable()
export class AdminAuthGuard implements CanActivate {

  constructor(private auth: AuthService, private userService: UserService) { }

  canActivate():Observable<boolean>{
    //need to retrieve custom param created in firebase "isAdmin"
    return this.auth.appUser$
    .map(appUser => appUser.isAdmin);//mapping result to boolean based on isAdmin property
  }

}
