import { Injectable } from '@angular/core';
import { AngularFireDatabase } from 'angularfire2/database';

@Injectable()
export class ProductService {

  constructor(private db: AngularFireDatabase) {}

  create(product){
    //return a promise in case if we want to something with it later
    return this.db.list('/products').push(product);
  }

  getAll(){
    return this.db.list('/products');
  }

  get(productId){
    return this.db.object('/products/' + productId)
  }

  update(productId, product){
    //firebase does not like $key.id property passed because the key should not be changed 
    return this.db.object('/products/' + productId).update(product);
  }

  delete(productId){
    return this.db.object('/products/' + productId).remove();
  }
  
}
