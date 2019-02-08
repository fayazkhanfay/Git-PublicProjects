import { Component, OnInit } from '@angular/core';
import { CategoryService } from 'src/app/category.service';
import { ProductService } from 'src/app/product.service';
import { Router, ActivatedRoute } from '@angular/router';
import 'rxjs/add/operator/take'; 

@Component({
  selector: 'app-product-form',
  templateUrl: './product-form.component.html',
  styleUrls: ['./product-form.component.css']
})
export class ProductFormComponent implements OnInit {
  categories$;
  product;
  id;

  constructor(
    private router: Router,
    private route: ActivatedRoute,
    private categoryService: CategoryService, 
    private productService: ProductService
    ) { 
    this.product ={};//for initial loading because will give null refernce exception 
                    // if set to empty array outside of contructor will get error
                    // Property 'title' does not exist on type '{}'. when ng build --prod
    this.categories$ = categoryService.getAll();

    //we don't need to subscribe because not using additional features
     this.id = this.route.snapshot.paramMap.get('id');
    if(this.id)
    {
      //quickly take but not unsubscribing: shortcut for unsubscribe vs onDestroy
       this.productService.get(this.id).take(1).subscribe(p => this.product = p);
    }
  }

  save(product){
    if (this.id) this.productService.update(this.id, product);
    else this.productService.create(product);
    
    this.router.navigate(['/admin/products']);
  }

  delete(){
    if(!confirm('Are you sure you want to delete this product?'))
      return;
    
    this.productService.delete(this.id);

    this.router.navigate(['/admin/products']);
    
  }

  
  ngOnInit() {
  }

}
