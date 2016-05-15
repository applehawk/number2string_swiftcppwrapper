//
//  ViewController.swift
//  NumberConverterSwift
//
//  Created by Teller.Vlad on 14.05.16.
//  Copyright © 2016 Teller.Vlad. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    @IBOutlet weak var numberField: UITextField!
    @IBOutlet weak var stringRepresent: UITextView!

    @IBAction func changeEditing(sender: UITextField) {
        if let numberText = sender.text {
            
            if NumberConverterCPPWrapper().isStringNumber(numberText) == true {
                stringRepresent.textColor = UIColor.blueColor()
                stringRepresent.text = NumberConverterCPPWrapper().convertStringNumberToWords(numberText)
            } else {
                stringRepresent.textColor = UIColor.redColor()
                stringRepresent.text = "WRONG_NUMBER".localized();
            }
            //if let number = Int64(numberText) {
            //    stringRepresent.textColor = UIColor.blueColor()
            //    stringRepresent.text = NumberConverterCPPWrapper().convertStringNumberToWords(numberText)
            //} else {
            //    stringRepresent.textColor = UIColor.redColor()
            //    stringRepresent.text = "WRONG_NUMBER".localized();
            //}
        }
    }
    @IBAction func endEditing(sender: AnyObject) {
        
    }
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

