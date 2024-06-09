/* 
? There are two types of relationships, association and inheritance. Associaton has 2 subtypes aggregation and composition.
? Association means there is a connection between two classes, they can communicate with each other.
? Associated objects has its own life cycle. There is no owner.

? Aggregation is a special form of association. It indicates a whole-part relationship. Each object has its own life cycle, and ownership exists.

? Composition is a specialized form of aggregation and association. It is a strong kind of "has-a" relationship.
? The life cycles of part and whole is tied. If the whole is destroyed, all parts are destroyed. They are created together.

! Association | Aggregation | Composition Example
* Yurt ve odalar arasındaki ilişki -> Composition (Yurt yıkılırsa odalar da yıkılır.)
* Odalar ve odanın içindeki eşyalar arasındaki ilişki -> Aggregation (Odalar boş olabilir, oda yıkıldığında eşyalar kalır.)
* Öğrenciler ve yurt arasındaki ilişki -> Association (Öğrenci yurda sahip değildir, zamanı geldiğinde yurttan çıkar, sadece kullanır.)


! No matter it is aggregation or composition, the destructor of the whole object is called first and then the destructors of the parts are called.
! In composition the part objects' constructors are called first and then the constructor of the whole object is called.
! In aggregation there is no such a rule, the constructors of the part objects and the whole object can be called in any order.
*/
