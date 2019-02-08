import { Component, OnInit } from '@angular/core';
import { ProductService } from '../product.service';
import { ActivatedRoute } from '@angular/router';
import { Product } from '../models/product';
import 'rxjs/add/operator/switchMap';

@Component({
  selector: 'app-products',
  templateUrl: './products.component.html',
  styleUrls: ['./products.component.css']
})
export class ProductsComponent  {
  products:Product[];//cannot sort a observable needs to be array
  filteredProducts: Product[];
  category: string;

  constructor(
    route: ActivatedRoute,
    productService: ProductService) {

    productService.getAll().subscribe(products => {
      this.products = products;
   
      //cannot use snapshot because it will continue to change route param. Thus, need to sub
    //this is just for routing of categories
    route.queryParamMap.subscribe(params => {
      this.category = params.get('category');
      
      //if category then match product array to category from DOM  or return whole product array
      this.filteredProducts = (this.category) ? 
        this.products.filter(p => p.category === this.category) :
        this.products;
      });
      
    });
    

    /*
    //with switchMap: gives ability to switch from one observable to another
   productService
    .getAll() 
    .switchMap(products => {
     this.products = products;//for somereason this would not work 
      return route.queryParamMap;
   })
   .subscribe(params => {
     this.category = params.get('category');
     
     //if category then match product array to category from DOM  or return whole product array
     this.filteredProducts = (this.category) ? 
       this.products.filter(p => p.category === this.category) :
       this.products;
     });
     this.categories$ = categoryService.getAll();
 //cannot use snapshot because it will continue to change route param. Thus, need to sub
//this is just for routing of categories
*/

   

    
    
  }

 
}
